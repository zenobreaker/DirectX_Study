#pragma once

class CDynamicCubeMap
{
public:
	CDynamicCubeMap(CShader* InShader);
	~CDynamicCubeMap();

	void Tick();
	void PreRender(const FVector& InPosition, const FVector& InScale);
	void Render(); 

public:
	CRenderTarget* GetRenderTarget() { return RenderTarget; }

private:
	struct FDesc
	{
		UINT Type;
		float Padding[3];

		FMatrix Views[6];
		FMatrix Projection;
	} Data;
	CConstantBuffer* CBuffer;

private:
	CShader* Shader;

	float Width = 256, Height = 256;
	float Near = 0.1f;
	float Far = 100.0f;
	float FOV = 0.25f;

	CRenderTarget* RenderTarget;
	CDepthStencil* DepthStencil;
	CViewport* Viewport;
	ID3DX11EffectShaderResourceVariable* sDynamicCubeMap;
};