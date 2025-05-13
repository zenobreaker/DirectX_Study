#pragma once

class CDepthStencil
{
public:
	CDepthStencil(float InWidth = 0.0f, float InHeight = 0.0f, bool InUseStencil = false, bool bCubeMap = false);
	~CDepthStencil();

	operator ID3D11DepthStencilView* () { return DSV; }
	operator const ID3D11DepthStencilView* () { return DSV; }

	operator ID3D11ShaderResourceView* () { return SRV; }
	operator const ID3D11ShaderResourceView* () { return SRV; }

	void ClearDepthStencil();
	void SaveTexture(wstring InFileName);

private:
	bool bUseStencil;
	float Width, Height;

	ID3D11Texture2D* Texture;
	ID3D11DepthStencilView* DSV;
	ID3D11ShaderResourceView* SRV;
};