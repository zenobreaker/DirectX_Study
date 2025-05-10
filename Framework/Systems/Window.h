#pragma once

class Window
{
public:
	static WPARAM Run(class IExecutable* InMain);

private:
	static void Create();
	static void Destroy();

	static LRESULT CALLBACK WndProc(HWND InHanlde, UINT InMessage, WPARAM InwParam, LPARAM InLParam);

	static void MainRender();

private:
	static class IExecutable* Main;
};

