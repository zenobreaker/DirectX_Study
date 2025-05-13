#pragma once

class CPostEffect : public CRenderer
{
private:
	enum class EPostEffectType
	{
		PS_Diffuse = 0,
		PS_Inverse,
		PS_Grayscale,
		PS_Grayscale2,
		PS_Saturation,
		PS_EdgeDetection,
		PS_Sharpness,
		PS_Sepia,
		PS_Vignette,
		PS_LensDistortion,
		PS_Interace,
		PS_Wiggle,
		PS_Blur,
		Max,
	} Type = EPostEffectType::PS_Diffuse;

public:
	CPostEffect();
	~CPostEffect();

	void Tick();

	void PreRender();
	void Render();

public:
	CRenderTarget* GetRenderTarget() { return RenderTarget; }

private:
	struct FDesc
	{
		FVector2D PixelSize;

		//Saturate = 0 : Grayscale
		//0 < Saturation < 1.0f : Desaturation
		//Saturation = 1.0f : Original
		//Saturation > 1.0f : Saturation
		float Saturation = 0.0f;
		float Sharpness = 0.0f;


		FMatrix ColorToSepia =
		{
			0.393f, 0.769f, 0.189f, 0.0f,
			0.349f, 0.686f, 0.168f, 0.0f,
			0.272f, 0.534f, 0.131f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		float VignettePower = 1.0f; // 1 - Linear, 1 > None-Linear
		FVector2D VignetteScale = FVector2D(1, 1);
		float Padding;

		float LensPower = 1.0f;
		FVector LensDistortion = FVector(-0.02f, -0.02f, -0.02f);

		float InteraceStrength = 1.0f;
		int InteraceValue = 2;

		FVector2D BlurSourceScale; //화면사이즈

		FVector2D WiggleOffset = FVector2D(50, 50);
		FVector2D WiggleAmount = FVector2D(0.005f, 0.005f);
	} Data;
	CConstantBuffer* CBuffer;

private:
	bool bShowGUI = false;

private:
	bool bMinimap = false;

private:
	CRenderTarget* RenderTarget;
	CDepthStencil* DepthStencil;
};