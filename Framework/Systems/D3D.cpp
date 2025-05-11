#include "Framework.h"
#include "D3D.h"

D3D* D3D::Instance = nullptr;
D3DDesc D3D::D3dDesc = D3DDesc();

D3D* D3D::Get()
{
	assert(Instance != nullptr);

	return Instance;
}

void D3D::Create()
{
	Instance = new D3D();
}

void D3D::Destroy()
{
	Delete(Instance);
}

const D3DDesc& D3D::GetDesc()
{
	return D3dDesc;
}

void D3D::SetDesc(const D3DDesc& InDesc)
{
	D3dDesc = InDesc;
}

void D3D::ClearRenderTargetView(Color InColor)
{
	DeviceContext->ClearRenderTargetView(RenderTargetView, InColor);
}

void D3D::Present()
{
	SwapChain->Present(0, 0);
}

D3D::D3D()
{
	CreateDevice();
	CreateRTV();
	CreateViewport();
}

D3D::~D3D()
{
	Release(RenderTargetView);

	Release(DeviceContext);
	Release(Device);

	Release(SwapChain);

}

void D3D::CreateDevice()
{
	// Create Device And SwapChain
	{
		DXGI_MODE_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_MODE_DESC));

		desc.Width = (UINT)D3dDesc.Width;
		desc.Height = (UINT)D3dDesc.Height;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ÁÖ»çÀ²
		desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.RefreshRate.Numerator = 0;
		desc.RefreshRate.Denominator = 1;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = desc;
		swapChainDesc.BufferCount = 1; 
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Windowed = true; 
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.OutputWindow = D3dDesc.Handle;


		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			nullptr, 
			D3D_DRIVER_TYPE_HARDWARE, 
			nullptr, 
			0, 
			nullptr, 
			0, 
			D3D11_SDK_VERSION, 
			&swapChainDesc, 
			&SwapChain, 
			&Device, 
			nullptr, 
			&DeviceContext
		);
		assert(hr >= 0 && "Create Device Failed!");
	}
}

void D3D::CreateRTV()
{
	HRESULT hr;

	ID3D11Texture2D* backBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),(void**)&backBuffer);
	assert(hr >= 0 && "Get BackBuffer Failed!");

	hr = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	assert(hr >= 0 && "Create RTV Failed!");

	Release(backBuffer);

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
}

void D3D::CreateViewport()
{
	Viewport = new D3D11_VIEWPORT();
	Viewport->TopLeftX = 0;
	Viewport->TopLeftY = 0;
	Viewport->Width = D3dDesc.Width;
	Viewport->Height= D3dDesc.Height;
	Viewport->MinDepth = 0;
	Viewport->MaxDepth = 0;

	DeviceContext->RSSetViewports(1, Viewport);
}


