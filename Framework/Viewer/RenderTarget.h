#pragma once

class CRenderTarget
{
public:
	CRenderTarget(float InWidth = 0.0f, float InHeight = 0.0f, DXGI_FORMAT InFormat = DXGI_FORMAT_R8G8B8A8_UNORM, bool bCubeMap = false);
	~CRenderTarget();

	operator ID3D11RenderTargetView* () { return RTV; }
	operator const ID3D11RenderTargetView* () { return RTV; }

	operator ID3D11ShaderResourceView* () { return SRV; }
	operator const ID3D11ShaderResourceView* () { return SRV; }

	void SaveTexture(wstring InFileName);

	void OMSetRenderTarget(class CDepthStencil* InDepthStencil);
	void ClearRenderTarget();

public:
	static void SetRenderTargets(CRenderTarget** InTargets, UINT InCount, class CDepthStencil* InDepthStencil);


private:
	float Width, Height;
	DXGI_FORMAT Format;

	ID3D11Texture2D* Texture;
	ID3D11RenderTargetView* RTV;
	ID3D11ShaderResourceView* SRV;
};