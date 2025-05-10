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

private:
	D3D();
	~D3D();

private:
	void CreateDevice();

private:
	static D3D* Instance;

private:
	static D3DDesc D3dDesc;

private:
	ID3D11Device* Device;
	IDXGISwapChain* SwapChain;
	ID3D11DeviceContext* DeviceContext;
};

