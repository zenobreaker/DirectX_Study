#pragma once

struct FD3DDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;

	float Width;
	float Height;

	FColor Background;
};

class CD3D
{
public:
	static CD3D* Get();

public:
	static void Create();
	static void Destroy();

public:
	static const FD3DDesc& GetDesc();
	static void SetDesc(const FD3DDesc& InDesc);

private:
	void CreateDevice();
	void CreateRTV();
	void CreateDSV();

public:
	ID3D11Device* GetDevice() { return Device; }
	ID3D11DeviceContext* GetDeviceContext() { return DeviceContext; }

	void SetRenderTarget();
	void ClearRenderTargetView(FColor InColor);
	void ClearDepthStencilView();
	void Present();

	void ResizeScreen(float InWidth, float InHeight);

private:
	CD3D();
	~CD3D();

private:
	static CD3D* Instance;

private:
	static FD3DDesc D3dDesc;

private:
	IDXGISwapChain* SwapChain;

	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;

	ID3D11RenderTargetView* RenderTargetView;

	ID3D11Texture2D* DSV_Texture;
	ID3D11DepthStencilView* DepthStencilView;
};

