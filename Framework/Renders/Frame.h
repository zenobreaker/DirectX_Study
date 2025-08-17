#pragma once

class CFrame
{
public:
	CFrame(CShader* InShader);
	~CFrame();
	
	void Render();

private:
    struct FFrameData
    {
        FMatrix View;
        FMatrix ViewInverse;
        FMatrix Projection;
        FMatrix ViewProjection;

		float RunningTime;
		float Padding[3];

		FPlane CullPlane[4];
		FPlane ClipPlane[4];
    } FrameData;

private:
	struct FLightData
	{
		FVector Direction;
		float Intensity;

		FColor Ambient;
		FColor Specular;
	} LightData;

private:
	CShader* Shader;

    CConstantBuffer* FrameBuffer;
    
	CConstantBuffer* LightBuffer;
	CConstantBuffer* PointLightBuffer;
	CConstantBuffer* SpotLightBuffer;

	CConstantBuffer* ProjectorBuffer;
	CTextureArray* ProjectorMaps;

private:
	struct FShadowDesc
	{
		FMatrix View;
		FMatrix Projection;

		FVector2D MapSize;
		float Bias = -0.0006f;

		UINT Quality = 0;
	} ShadowData;

private:
	CConstantBuffer* ShadowBuffer;
	ESRV* sShadowMap;

};