#include "Framework.h"
#include "D3D.h"

CD3D* CD3D::Instance = nullptr;

FD3DDesc CD3D::D3dDesc = FD3DDesc();


CD3D* CD3D::Get()
{
	assert(Instance != nullptr);

	return Instance;
}

void CD3D::Create()
{
	assert(Instance == nullptr);

	Instance = new CD3D();
}

void CD3D::Destroy()
{
	Delete(Instance);
}

const FD3DDesc& CD3D::GetDesc()
{
	return D3dDesc;
}

void CD3D::SetDesc(const FD3DDesc& InDesc)
{
	D3dDesc = InDesc;
}

void CD3D::SetRenderTarget()
{
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
}

void CD3D::ClearRenderTargetView(FColor InColor)
{
	DeviceContext->ClearRenderTargetView(RenderTargetView, InColor);
}

void CD3D::ClearDepthStencilView()
{
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1, 0);
}

void CD3D::Present()
{
	SwapChain->Present(0, 0);
}

void CD3D::ResizeScreen(float InWidth, float InHeight)
{
	if (InWidth < 1 || InHeight < 1)
		return;

	D3dDesc.Width = InWidth;
	D3dDesc.Height = InHeight;

	Release(RenderTargetView);
	Release(DSV_Texture);
	Release(DepthStencilView);
	{
		SwapChain->ResizeBuffers(0, (UINT)InWidth, (UINT)InHeight, DXGI_FORMAT_UNKNOWN, 0);
	}
	CreateRTV();
	CreateDSV();
}

CD3D::CD3D()
{
	CreateDevice();
	CreateRTV();
	CreateDSV();
}

CD3D::~CD3D()
{
	Release(DepthStencilView);
	Release(DSV_Texture);
	Release(RenderTargetView);
	Release(DeviceContext);
	Release(Device);
	Release(SwapChain);
}

void CD3D::CreateDevice()
{
	//Create Device And SwapChain
	{
		DXGI_MODE_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_MODE_DESC));

		desc.Width = (UINT)D3dDesc.Width;
		desc.Height = (UINT)D3dDesc.Height;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
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
		assert(hr >= 0 && "Device 생성 실패");
	}
}

void CD3D::CreateRTV()
{
	HRESULT hr;

	ID3D11Texture2D* backBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	assert(hr >= 0 && "Back Buffer 가져오기 실패");

	hr = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	assert(hr >= 0 && "RTV 생성 실패");

	Release(backBuffer);
}

void CD3D::CreateDSV()
{
	DXGI_FORMAT format = DXGI_FORMAT_D32_FLOAT;

	//Create Texture - DSV
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = (UINT)D3dDesc.Width;
		desc.Height = (UINT)D3dDesc.Height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.Usage = D3D11_USAGE_DEFAULT;

		Check(Device->CreateTexture2D(&desc, nullptr, &DSV_Texture));
	}

	//Create DSV
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		desc.Format = format;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		Check(Device->CreateDepthStencilView(DSV_Texture, &desc, &DepthStencilView));
	}
}

