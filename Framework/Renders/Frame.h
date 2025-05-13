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
};