#pragma once

struct D3DDesc
{
	wstring AppName;	 // 애플리케이션 이름 
	HINSTANCE Instance;	 // 프로그램의 시작 주소 
	HWND Handle;		 // 윈도우 창

	float Width;		// 창의 가로
	float Height;		// 창의 높이

	Color Background;
};

class D3D
{
public:
	static D3D* Get();

public:
	static void Create();
	static void Destroy();

public:
	static const D3DDesc& GetDesc();
	static void SetDesc(const D3DDesc& InDesc);

public:
	IDXGISwapChain* GetSwapChain() { return SwapChain; }

	ID3D11Device* GetDevice() { return Device; }
	ID3D11DeviceContext* GetDeviceContext() { return DeviceContext; }

	void ClearRenderTargetView(Color InColor);
	void Present();

private:
	D3D();
	~D3D();

private:
	void CreateDevice();
	void CreateRTV(); 
	void CreateViewport(); 

private:
	static D3D* Instance;

private:
	static D3DDesc D3dDesc;

private:
	IDXGISwapChain* SwapChain;

	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;

	ID3D11RenderTargetView* RenderTargetView; 

	D3D11_VIEWPORT* Viewport; 
};

