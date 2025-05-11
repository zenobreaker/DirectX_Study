#include "Framework.h"
#include "Window.h"
#include "IExecutable.h"

IExecutable* Window::Main = nullptr;


WPARAM Window::Run(IExecutable* InMain)
{
	Create();

	D3D::Create();

	Main = InMain;
	Main->Initialize();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) //Game Loop
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

	D3D::Destroy();

	Destroy();

	return msg.wParam;
}

void Window::Create()
{
	D3DDesc Desc = D3D::GetDesc();

	{
		WNDCLASSEX WndClass;
		WndClass.cbSize = sizeof(WNDCLASSEX);
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		WndClass.lpfnWndProc = WndProc;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hInstance = Desc.Instance;
		WndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		WndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		WndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 2);
		WndClass.lpszMenuName = nullptr;
		WndClass.lpszClassName = Desc.AppName.c_str();

		const ATOM Check = RegisterClassEx(&WndClass);
		assert(Check != 0);
	}

	//Create Window Handle
	Desc.Handle = CreateWindowEx
	(
		0,
		Desc.AppName.c_str(),
		Desc.AppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, //Default - X
		CW_USEDEFAULT, //Default - Y
		static_cast<int>(Desc.Width),
		static_cast<int>(Desc.Height),
		nullptr,
		nullptr,
		Desc.Instance,
		nullptr
	);
	assert(Desc.Handle != nullptr);

	ShowWindow(Desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(Desc.Handle);
	SetFocus(Desc.Handle);
	ShowCursor(true);

	D3D::SetDesc(Desc);
}

void Window::Destroy()
{
	D3DDesc Desc = D3D::GetDesc();

	DestroyWindow(Desc.Handle);
	UnregisterClass(Desc.AppName.c_str(), Desc.Instance);
}

LRESULT Window::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
	if (InMessage == WM_KEYDOWN)
	{
		if (InwParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	if (InwParam == 0x41) // 'A'
	{
		MessageBox(nullptr, L"Test", L"Test", MB_OK);
		return 0;
	}


	if (InMessage == WM_CLOSE || InMessage == WM_DESTROY)
	{
		PostQuitMessage(0);
	}

	return DefWindowProc(InHandle, InMessage, InwParam, InlParam);
}

void Window::MainRender()
{
	D3D::Get()->ClearRenderTargetView(Color(0, 0, 0, 0)); 

	Main->Tick();
	Main->Render();

	D3D::Get()->Present(); 
}