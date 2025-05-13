#include "Framework.h"
#include "Window.h"
#include "IExecutable.h"

IExecutable* CWindow::Main = nullptr;

WPARAM CWindow::Run(IExecutable* InMain, bool bGameLoop)
{
	Create();

	CD3D::Create();
	CGui::Create();
	CKeyboard::Create();
	CTimer::Create();
	CMouse::Create();
	CContext::Create();
	CLighting::Create();
	CProjector::Create();
	CShaders::Create();

	Main = InMain;
	Main->Initialize();


	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (bGameLoop) //Game Loop
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg); //WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			MainRender();
		}
	}


	Main->Destroy();

	CShaders::Destroy();
	CProjector::Destroy();
	CLighting::Destroy();
	CContext::Destroy();
	CMouse::Destroy();
	CTimer::Destroy();
	CKeyboard::Destroy();
	CGui::Destroy();
	CD3D::Destroy();

	Destroy();

	return msg.wParam;
}

void CWindow::Create()
{
	FD3DDesc desc = CD3D::GetDesc();

	//Regist CWindow Class
	{
		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = desc.Instance;
		wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = desc.AppName.c_str();

		ATOM check = RegisterClassEx(&wndClass);
		assert(check != 0);
	}

	//Create CWindow Handle
	desc.Handle = CreateWindowEx
	(
		0,
		desc.AppName.c_str(),
		desc.AppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, //Default - X
		CW_USEDEFAULT, //Default - Y
		(int)desc.Width,
		(int)desc.Height,
		nullptr,
		nullptr,
		desc.Instance,
		nullptr
	);
	assert(desc.Handle != nullptr);


	RECT rect = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow(desc.Handle, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);
	ShowCursor(true);

	CD3D::SetDesc(desc);
}

void CWindow::Destroy()
{
	FD3DDesc desc = CD3D::GetDesc();

	DestroyWindow(desc.Handle);
	UnregisterClass(desc.AppName.c_str(), desc.Instance);
}

LRESULT CWindow::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
	CMouse::Get()->WndProc(InMessage, InwParam, InlParam);

	if (CGui::Get()->WndProc(InHandle, InMessage, InwParam, InlParam))
		return TRUE;


	if (InMessage == WM_SIZE)
	{
		if (Main != nullptr)
		{
			float width = (float)LOWORD(InlParam);
			float height = (float)HIWORD(InlParam);

			if (CD3D::Get() != nullptr)
				CD3D::Get()->ResizeScreen(width, height);

			if (CContext::Get() != nullptr)
				CContext::Get()->ResizeScreen();
		}
	}

	if (InMessage == WM_KEYDOWN)
	{
		if (InwParam == VK_ESCAPE)
		{
			PostQuitMessage(0);

			return 0;
		}
	}

	if (InMessage == WM_CLOSE || InMessage == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(InHandle, InMessage, InwParam, InlParam);
}

void CWindow::MainRender()
{
	CGui::Get()->Tick();
	CTimer::Get()->Tick();
	CMouse::Get()->Tick();
	CContext::Get()->Tick();
	CLighting::Get()->Tick();
	CProjector::Get()->Tick();
	
	Main->Tick();

	//Pre Rendering
	{
		Main->PreRender();
	}

	//Rendering
	{
		CD3D::Get()->SetRenderTarget();
		CD3D::Get()->ClearRenderTargetView(CD3D::GetDesc().Background);
		CD3D::Get()->ClearDepthStencilView();

		CContext::Get()->Render();

		Main->Render();
	}

	//Post Rendering
	{
		Main->PostRender();
	}

	CGui::Get()->Render();
	CD3D::Get()->Present();
}
