#pragma once

class CBlur : public CRenderer
{
private:
	enum class EBlurType
	{
		Diffuse,
		Blur,
		RadialBlur,
		GaussianBlur,
		GaussianBlurMRT,
		Max,
	};

public:
	CBlur();
	~CBlur();

	void Tick();

	void Begin_PreRender();
	void End_PreRender();

	void Render();

private:
	void Render(UINT InPass);

public:
	CRenderTarget* GetRenderTarget() { return RenderTargets[0]; }

private:
	struct FDesc
	{
		FVector2D PixelSize;
		float Padding[2];

		//PS_Blur
		UINT Count = 8;
		float Padding2[3];

		//PS_RadialBlur
		float Radius = 0.6f;
		float Amount = 0.04f; //4%
		FVector2D Center = FVector2D(0.5f, 0.5f);

		//PS_GaussianBlur
		int GaussianCount = 6;
		float Padding3[3];
	} Data;
	CConstantBuffer* CBuffer;

private:
	bool bShowGUI = false;

private:
	bool bBegin = false;

private:
	EBlurType Type = EBlurType::Diffuse;

private:
	CRenderTarget* RenderTargets[4];
	CDepthStencil* DepthStencil;
	CViewport* Viewport;

	ID3DX11EffectShaderResourceVariable* sBlurMap;
	ID3DX11EffectShaderResourceVariable* sGaussianBlurMaps;
};