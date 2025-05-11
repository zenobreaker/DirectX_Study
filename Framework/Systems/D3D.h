#pragma once

struct D3DDesc
{
	wstring AppName;	 // ���ø����̼� �̸� 
	HINSTANCE Instance;	 // ���α׷��� ���� �ּ� 
	HWND Handle;		 // ������ â

	float Width;		// â�� ����
	float Height;		// â�� ����

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

