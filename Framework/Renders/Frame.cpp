#include "Framework.h"
#include "Frame.h"

CFrame::CFrame(CShader* InShader)
	: Shader(InShader)
{
	FrameBuffer = new CConstantBuffer(Shader, "CB_Context", &FrameData, sizeof(FFrameData));
	LightBuffer = new CConstantBuffer(Shader, "CB_GlobalLight", &LightData, sizeof(FLightData));

	
	FPointLightDesc* pointLight = CLighting::Get()->GetPointLightData();
	PointLightBuffer = new CConstantBuffer(Shader, "CB_PointLights", pointLight, sizeof(FPointLightDesc));

	FSpotLightDesc* spotLight = CLighting::Get()->GetSpotLightData();
	SpotLightBuffer = new CConstantBuffer(Shader, "CB_SpotLights", spotLight, sizeof(FSpotLightDesc));


	const vector<wstring> projectorMapFiles = CProjector::Get()->GetTextureFiles();
	ProjectorMaps = new CTextureArray(Shader, "ProjectorMaps", projectorMapFiles);

	FProjectorDesc* projector = CProjector::Get()->GetData();
	ProjectorBuffer = new CConstantBuffer(Shader, "CB_Projectors", projector, sizeof(FProjectorDesc));
}

CFrame::~CFrame()
{
	Delete(FrameBuffer);
	Delete(LightBuffer);
	Delete(PointLightBuffer);
	Delete(SpotLightBuffer);
	Delete(ProjectorMaps);
	Delete(ProjectorBuffer);
}

void CFrame::Render()
{
	//Frame Buffer
	{
		FrameData.View = CContext::Get()->GetViewMatrix();
		FrameData.ViewInverse = FMatrix::Invert(FrameData.View);

		FrameData.Projection = CContext::Get()->GetProjectionMatrix();
		FrameData.ViewProjection = FrameData.View * FrameData.Projection;

		FrameData.RunningTime = CTimer::Get()->GetRunningTime();

		FrameBuffer->Render();
	}
	
	//Light Buffer
	{
		LightData.Direction = CContext::Get()->GetLightDirection();
		LightData.Intensity = CContext::Get()->GetLightIntensity();

		LightData.Ambient = CContext::Get()->GetAmbientColor();
		LightData.Specular = CContext::Get()->GetSpecularColor();

		LightBuffer->Render();
	}

	PointLightBuffer->Render();
	SpotLightBuffer->Render();

	
	//Projector Buffer
	{
		ProjectorMaps->Render();
		ProjectorBuffer->Render();
	}
}
