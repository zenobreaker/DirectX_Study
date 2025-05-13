#include "Framework.h"
#include "DepthStencil.h"

CDepthStencil::CDepthStencil(float InWidth, float InHeight, bool InUseStencil, bool bCubeMap)
	: bUseStencil(InUseStencil)
{
	this->Width = (InWidth < 1) ? CD3D::GetDesc().Width : InWidth;
	this->Height = (InHeight < 1) ? CD3D::GetDesc().Height : InHeight;

	
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = (UINT)this->Width;
	textureDesc.Height = (UINT)this->Height;
	textureDesc.ArraySize = 1;
	textureDesc.Format = bUseStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;

	if (bCubeMap)
	{
		textureDesc.ArraySize = 6;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}

	Check(CD3D::Get()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &Texture));


	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Format = bUseStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	if (bCubeMap)
	{
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		dsvDesc.Texture2DArray.ArraySize = 6;
	}

	Check(CD3D::Get()->GetDevice()->CreateDepthStencilView(Texture, &dsvDesc, &DSV));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = bUseStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	if (bCubeMap)
	{
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MipLevels = 1;
	}

	Check(CD3D::Get()->GetDevice()->CreateShaderResourceView(Texture, &srvDesc, &SRV));
}

CDepthStencil::~CDepthStencil()
{
	Release(Texture);
	Release(DSV);
	Release(SRV);
}

void CDepthStencil::ClearDepthStencil()
{
	UINT flags = D3D11_CLEAR_DEPTH;
	flags = bUseStencil ? flags | D3D11_CLEAR_STENCIL : flags;

	CD3D::Get()->GetDeviceContext()->ClearDepthStencilView(DSV, flags, 1, 0);
}

void CDepthStencil::SaveTexture(wstring InFileName)
{
	Check(D3DX11SaveTextureToFile(CD3D::Get()->GetDeviceContext(), Texture, D3DX11_IFF_PNG, InFileName.c_str()));
}