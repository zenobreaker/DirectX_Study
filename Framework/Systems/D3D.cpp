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


D3D::D3D()
{
	CreateDevice();
}

D3D::~D3D()
{
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
			1,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&SwapChain,
			&Device,
			nullptr,
			&DeviceContext
		);
		assert(hr >= 0 && "Create device Failed!");
	}
}