#pragma once

class CGui
{
public:
	static void Create();
	static void Destroy();

	static CGui* Get();

public:
	void Tick();
	void Render();

	LRESULT WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);

public:
	void RenderText(float x, float y, float r, float g, float b, string content);
	void RenderText(float x, float y, float r, float g, float b, float a, string content);

private:
	static CGui* Instance;

private:
	CGui();
	~CGui();

private:
	struct FGuiText
	{
		FVector2D Position;
		FColor Color;
		string Content;
	};

private:
	vector<FGuiText> Contents;
};