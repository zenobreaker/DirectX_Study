#pragma once

class CTexture
{
public:
	CTexture(wstring InFileName, bool bDefaultPath = true);
	CTexture(CShader* InShader, string InParamName, wstring InFileName, bool bDefaultPath = true);
	~CTexture();

	void Render();

public:
	ID3D11ShaderResourceView* GetSRV() { return SRV; }

public:
	UINT GetWidth() { return Metadata.width; }
	UINT GetHeight() { return Metadata.height; }

public:
	static DirectX::TexMetadata GetMetaData(wstring InFilePath);
	static ID3D11ShaderResourceView* CreateSRV(wstring InFilePath, DirectX::TexMetadata& InMetadata);

public:
	D3D11_TEXTURE2D_DESC ReadPixel(vector<FColor>& OutPixel);
	D3D11_TEXTURE2D_DESC ReadPixel(DXGI_FORMAT InFormat, vector<FColor>& OutPixel);
	D3D11_TEXTURE2D_DESC ReadPixel(ID3D11Texture2D* InSource, DXGI_FORMAT InFormat, vector<FColor>& OutPixel);

private:
	CShader* Shader;

private:
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3DX11EffectShaderResourceVariable* sSRV = nullptr;

	DirectX::TexMetadata Metadata;

private:
	wstring FileName;
};

///////////////////////////////////////////////////////////////////////////////

class CTextureArray
{
public:
	CTextureArray(CShader* InShader, string InParamName, const vector<wstring>& InNames, bool bDefaultPath = true, UINT InWidth = 256, UINT InHeight = 256, UINT InMipLevels = 1);
	~CTextureArray();

	void Render();

private:
	vector<ID3D11Texture2D*> CreateTexture(const vector<wstring>& InNames, UINT InWidth, UINT InHeight, UINT InMipLevels);

private:
	CShader* Shader;

	ID3D11ShaderResourceView* SRV;
	ID3DX11EffectShaderResourceVariable* sSRVs = nullptr;
};