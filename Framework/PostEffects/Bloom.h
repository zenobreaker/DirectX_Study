#pragma once

class CBloom : public CRenderer
{
private:
	enum class EBloomType
	{
		Diffuse,
		Luminosity,
		GaussianBlurCombiend,
		Composite,
		ColorGrading,
		Max,
	} Type = EBloomType::ColorGrading;

public:
	CBloom();
	~CBloom();

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
		
		float Threshold = 0.1f;
		int SamplingCount = 6;

		FColor GradeColor = FColor(1.0f, 0.5f, 0.0f, 1.0f); //강조하고 싶은 RGB 색상
		float Amount = 0.5f; //보정량
		float Correlation = 0.5f; //상관성(<= 0.5f)
		float Concentration = 2.0f; //농도  
		float Padding;
	} Data;
	CConstantBuffer* CBuffer;

private:
	bool bShowGUI = false;
	bool bApply = true;

private:
	bool bBegin = false;

private:
	CRenderTarget* RenderTargets[7];
	CDepthStencil* DepthStencil;
	CViewport* Viewport;

private:
	ID3DX11EffectShaderResourceVariable* sBloomMap;
	ID3DX11EffectShaderResourceVariable* sGaussianBlurMaps;
	ID3DX11EffectShaderResourceVariable* sLuminosityMap;
	ID3DX11EffectShaderResourceVariable* sBlurResultMap;
};