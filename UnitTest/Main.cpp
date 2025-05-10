#include "Pch.h"
#include "Main.h"
#include "Systems/Window.h"

#include "Line.h"

void Main::Initialize()
{
	Push(new Line());
}

void Main::Destroy()
{
	for (IExecutable* execute : executes)
	{
		execute->Destroy();

		Delete(execute);
	}
}

void Main::Tick()
{
	for (IExecutable* execute : executes)
		execute->Tick();
}

void Main::Render()
{
	for (IExecutable* execute : executes)
		execute->Render();
}

void Main::Push(IExecutable* exceute)
{
	executes.push_back(exceute);

	exceute->Initialize();
}



int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int comment)
{
	D3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = InInstance;
	desc.Handle = nullptr;

	desc.Width = 1280;
	desc.Height = 720;

	desc.Background = Color(0.3f, 0.3f, 0.3f, 1.0f);

	D3D::SetDesc(desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);

	Delete(main)

	return wParam;
}
