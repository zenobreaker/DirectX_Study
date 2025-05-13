#pragma once

class CBillboard : public CRenderer
{
public:
	CBillboard(wstring InShader = L"00_Billboard.fxo");
	~CBillboard();

	void Tick();
	void Render();

	void AddTexture(wstring InFile);
	void AddPosition(const FVector& InPosition, const FVector2D& InScale, UINT InMapIndex);

private:
	struct FVertexBillboard
	{
		FVector Position;
		FVector2D Uv;
		UINT MapIndex;
	};

private:
	struct FDesc
	{
		float Brightness = 1.25f;
		float Padding[3];
	} Data;
	CConstantBuffer* CBuffer;

private:
	UINT Pass = 5;

	vector<FVertexBillboard> Vertices;

	vector<wstring> TextureNames;
	CTextureArray* TextureArray = nullptr;
};