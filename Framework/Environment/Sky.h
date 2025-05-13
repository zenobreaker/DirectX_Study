#pragma once

class CSky
{
public:
	CSky(wstring InTextureFile, wstring InShader = L"00_Sky.fxo", float InScale = 3.0f);
	~CSky();

	void Tick();
	void Render();

	struct FDesc
	{
		FColor HorizonTwilightColor = FColor(0.6f, 0.24f, 0.0f, 1.0f);
		FColor CeilingTwilightColor = FColor(0.17f, 0.15f, 0.15f, 1.0f);

		FColor HorizonDaylight = FColor(1.0f, 1.0f, 1.0f, 1.0f);
		FColor CeilingDaylight = FColor(0.72f, 0.75f, 0.98f, 1.0f);

		FColor HorizonNight = FColor(0.1f, 0.1f, 0.1f, 1.0f);
		FColor CeilingNight = FColor(0.0f, 0.0f, 0.0f, 1.0f);

		float HorizonStartY = 0.4f;
		float Tiling = 5.0f;
		float StarBrightness = 5.0f;

		float CubeMapAlpha = 0.7f;
	} Data;

	CConstantBuffer* CBuffer;

private:
	float Scale;

private:
	CShader* Shader;
	CMeshRender* Mesh;
	CTransform* Transform;

	ID3D11ShaderResourceView* SRV;
	ID3DX11EffectShaderResourceVariable* sSRV;
};