#pragma once

class CWindow
{
public:
	static WPARAM Run(class IExecutable* InMain, bool bGameLoop = true);

private:
	static void Create();
	static void Destroy();

	static LRESULT CALLBACK WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);

	static void MainRender();

private:
	static class IExecutable* Main;
};

