#pragma once

class CTerrain : public CRenderer
{
public:
	CTerrain(wstring InHeightMapFileName, wstring InShader = L"00_Terrain.fxo", float InMaxHeight = 25.0f);
	~CTerrain();

	void Tick();
	void Render();


public:
	UINT GetWidth() { return Width; }
	UINT GetHeight() { return Height; }

	float GetY(UINT x, UINT z);
	const FVector4& GetWeights(UINT x, UINT z);

	
	float GetHeightScale() { return HeightScale; }

	float GetHeightLowRatio() { return HeightLowRatio * HeightScale; }
	float GetHeightHighRatio() { return HeightHighRatio * HeightScale; }

	float GetHeightGentleAngle() { return HeightGentleAngle; }
	float GetHeightSteepAngle() { return HeightSteepAngle; }

private:
	void Regeneration();

private:
	struct FVertexTerrain
	{
		FVertexTerrain()
			: Position(0, 0, 0)
			, Uv(0, 0)
			, Normal(0, 0, 0)
			, Tangent(0, 0, 0)
			, Weights(0, 0, 0, 0)
		{

		}

		FVector Position;
		FVector2D Uv;
		FVector Normal;
		FVector Tangent;
		FVector4 Weights;
	};

public:
	void SetBaseMap(wstring InFile, wstring InNormalFile);
	void SetLowMap(wstring InFile, wstring InNormalFile);
	void SetHighMap(wstring InFile, wstring InNormalFile);
	void SetSlopeMap(wstring InFile, wstring InNormalFile);

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalAndTangentData();
	void CreateWeightData();

private:
	struct FDesc
	{
		FVector2D Tiling = FVector2D(32, 32);
		float Padding[2];

		FColor Specular = FColor(0.25f, 0.25f, 0.25f, 1000);
	} Data;
	CConstantBuffer* CBuffer;

private:
	wstring HeightFileName;
	CTexture* HeightMap;

	float HeightScale;

	float HeightLowRatio = 0.2f;
	float HeightHighRatio = 0.3f;

	float HeightGentleAngle = 25.0f;
	float HeightSteepAngle = 80.0f;


	UINT Width, Height;

	FVertexTerrain* Vertices = nullptr;
	UINT* Indices = nullptr;

	wstring TextureFiles[4];
	CTextureArray* Textures = nullptr;

	wstring NormalFiles[4];
	CTextureArray* NormalTextures = nullptr;
};