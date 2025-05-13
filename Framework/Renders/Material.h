#pragma once

class CMaterial
{
public:
	CMaterial();
	CMaterial(CShader* InShader);
	~CMaterial();

	void Render();
	
public:
	bool GetDraw() { return bDraw; }
	void SetDraw(bool InValue) { bDraw = InValue; }

public:
	void SetTechnique(UINT InValue) { Technique = InValue; }
	void SetPass(UINT InValue) { Pass = InValue; }

public:
	void SetAmbient(const FColor& InColor) { Data.Ambient = InColor; }
	void SetDiffuse(const FColor& InColor) { Data.Diffuse = InColor; }
	void SetSpecular(const FColor& InColor) { Data.Specular = InColor; }
	void SetEmissive(const FColor& InColor) { Data.Emissive = InColor; }

	void SetTiling(const FVector2D& InValue) { Data.Tiling = InValue; }
	void SetOffset(const FVector2D& InValue) { Data.Offset = InValue; }

public:
	void SetDiffuseMap(wstring InFilePath, bool bDefaultPath = true);
	void SetSpecularMap(wstring InFilePath, bool bDefaultPath = true);
	void SetNormalMap(wstring InFilePath, bool bDefaultPath = true);

private:
	bool bDraw = true;
	CShader* Shader = nullptr;

private:
	UINT Technique = 0;
	UINT Pass = 0;

private:
	struct FDesc
	{
		FColor Ambient = FColor::Black;
		FColor Diffuse = FColor::White;
		FColor Specular = FColor::Black;
		FColor Emissive = FColor::Black;
		
		FVector2D Tiling = FVector2D::One;
		FVector2D Offset = FVector2D::Zero;
	} Data;

	CConstantBuffer* CBuffer = nullptr;

private:
	CTexture* DiffuseMap = nullptr;
	CTexture* SpecularMap = nullptr;
	CTexture* NormalMap = nullptr;
};