#include "Framework.h"
#include "RenderTarget.h"

CRenderTarget::CRenderTarget(float InWidth, float InHeight, DXGI_FORMAT InFormat, bool bCubeMap)
	: Format(InFormat)
{
	this->Width = (InWidth < 1) ? CD3D::GetDesc().Width : InWidth;
	this->Height = (InHeight < 1) ? CD3D::GetDesc().Height : InHeight;


	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = (UINT)this->Width;
	textureDesc.Height = (UINT)this->Height;
	textureDesc.ArraySize = 1;
	textureDesc.Format = Format;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

	if (bCubeMap)
	{
		textureDesc.ArraySize = 6;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}

	Check(CD3D::Get()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &Texture));

	
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	if (bCubeMap)
	{
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.MipSlice = 0; 
		rtvDesc.Texture2DArray.FirstArraySlice = 0;
		rtvDesc.Texture2DArray.ArraySize = 6;
	}
	
	Check(CD3D::Get()->GetDevice()->CreateRenderTargetView(Texture, &rtvDesc, &RTV));


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	if (bCubeMap)
	{
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels = 1;
	}

	Check(CD3D::Get()->GetDevice()->CreateShaderResourceView(Texture, &srvDesc, &SRV));
}

CRenderTarget::~CRenderTarget()
{
	Release(Texture);
	Release(RTV);
	Release(SRV);
}

void CRenderTarget::SaveTexture(wstring InFileName)
{
	Check(D3DX11SaveTextureToFile(CD3D::Get()->GetDeviceContext(), Texture, D3DX11_IFF_PNG, InFileName.c_str()));
}

void CRenderTarget::OMSetRenderTarget(CDepthStencil* InDepthStencil)
{
	CD3D::Get()->GetDeviceContext()->OMSetRenderTargets(1, &RTV, *InDepthStencil);
}

void CRenderTarget::ClearRenderTarget()
{
	FColor color = CD3D::GetDesc().Background;

	CD3D::Get()->GetDeviceContext()->ClearRenderTargetView(RTV, color);
}

void CRenderTarget::SetRenderTargets(CRenderTarget** InTargets, UINT InCount, CDepthStencil* InDepthStencil)
{
	vector<ID3D11RenderTargetView*> rtvs;
	for (UINT i = 0; i < InCount; i++)
	{
		InTargets[i]->ClearRenderTarget();

		rtvs.push_back(*InTargets[i]);
	}

	InDepthStencil->ClearDepthStencil();

	CD3D::Get()->GetDeviceContext()->OMSetRenderTargets(rtvs.size(), &rtvs[0], *InDepthStencil);
}
