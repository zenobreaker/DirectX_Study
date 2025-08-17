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

	ShadowBuffer = new CConstantBuffer(Shader, "CB_Shadow", &ShadowData, sizeof(FShadowDesc));
	sShadowMap = Shader->AsSRV("ShadowMap");
}

CFrame::~CFrame()
{
	Delete(FrameBuffer);
	Delete(LightBuffer);
	Delete(PointLightBuffer);
	Delete(SpotLightBuffer);
	Delete(ProjectorMaps);
	Delete(ProjectorBuffer);
	Delete(ShadowBuffer);
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

	// Shadow Buffer; 
	{
		CContext::Get()->GetShadow()->CalcViewProjection();
		ShadowData.View = CContext::Get()->GetShadow()->GetView();
		FMatrix view = CContext::Get()->GetShadow()->GetView();
		printf("Frame View row0: %f %f %f %f\n", view.M11, view.M12, view.M13, view.M14);
		printf("Frame View row3: %f %f %f %f\n", view.M41, view.M42, view.M43, view.M44);
		ShadowData.Projection = CContext::Get()->GetShadow()->GetProjection();

		FVector2D mapSize;
		mapSize.X = (float)CContext::Get()->GetShadow()->GetWidth();
		mapSize.Y = (float)CContext::Get()->GetShadow()->GetHeight();

		ShadowData.MapSize = mapSize; 
		ShadowData.Bias = CContext::Get()->GetShadow()->GetBias(); 
		ShadowData.Quality= CContext::Get()->GetShadow()->GetQuaility(); 

		ShadowBuffer->Render();
		sShadowMap->SetResource(*CContext::Get()->GetShadow());
	}
}
