#pragma once

class CSun : public CRenderer
{
public:
	CSun(wstring InShader = L"00_Sun.fxo");
	~CSun();

	void Tick();
	void Render();

private:
	struct FDesc
	{
		float Scale = 1.0f;
		float AlphaHeightY = 0.91f;

		float Padding[2];
	} Data;
	CConstantBuffer* CBuffer;

private:
	float PositionX = -2.5f;
	float DrawDistance = 10.0f;

	CTexture* Texture;
};