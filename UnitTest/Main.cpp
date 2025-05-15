#include "Pch.h"
#include "Main.h"
#include "Systems/Window.h"

#include "Demo.h"

void CMain::Initialize()
{
	Push_Main(CDemo);
}

void CMain::Destroy()
{
	for (IExecutable* execute : Executes)
	{
		execute->Destroy();

		Delete(execute);
	}
}

void CMain::Tick()
{
	for (IExecutable* execute : Executes)
		execute->Tick();
}

void CMain::PreRender()
{
	for (IExecutable* execute : Executes)
		execute->PreRender();
}

void CMain::Render()
{
	for (IExecutable* execute : Executes)
		execute->Render();
}

void CMain::PostRender()
{
	for (IExecutable* execute : Executes)
		execute->PostRender();
}

void CMain::Push(IExecutable* InExecutable)
{
	Executes.push_back(InExecutable);

	InExecutable->Initialize();
}

///////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int command)
{
	FD3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = InInstance;
	desc.Handle = nullptr;

	desc.Width = 1600;
	desc.Height = 900;

	desc.Background = FColor(0.3f, 0.3f, 0.3f, 1.0f);

	CD3D::SetDesc(desc);


	CMain* main = new CMain();
	WPARAM wParam = CWindow::Run(main);
	Delete(main);

	return wParam;
}