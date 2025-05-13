#include "Framework.h"
#include "Bloom.h"

CBloom::CBloom()
	: CRenderer(L"00_Bloom.fxo")
{
	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	RenderTargets[0] = new CRenderTarget(width, height); //PS_Diffuse
	RenderTargets[1] = new CRenderTarget(width, height); //PS_Luminosity
	RenderTargets[2] = new CRenderTarget(width, height); //PS_GaussianBlurMRT - X
	RenderTargets[3] = new CRenderTarget(width, height); //PS_GaussianBlurMRT - Y  
	RenderTargets[4] = new CRenderTarget(width, height); //PS_GaussianBlurCombiend
	RenderTargets[5] = new CRenderTarget(width, height); //PS_Composite
	RenderTargets[6] = new CRenderTarget(width, height); //Color PS_ColorGrading

	DepthStencil = new CDepthStencil(width, height);
	Viewport = new CViewport(width, height);


	FVertex vertices[6];
	vertices[0].Position = FVector(-1.0f, -1.0f, 0.0f);
	vertices[1].Position = FVector(-1.0f, +1.0f, 0.0f);
	vertices[2].Position = FVector(+1.0f, -1.0f, 0.0f);
	vertices[3].Position = FVector(+1.0f, +1.0f, 0.0f);

	VBuffer = new CVertexBuffer(vertices, 4, sizeof(FVertex));
	CBuffer = new CConstantBuffer(Shader, "CB_Bloom", &Data, sizeof(FDesc));

	sBloomMap = Shader->AsSRV("BloomMap");
	sGaussianBlurMaps = Shader->AsSRV("GaussianBlurMaps");
	sLuminosityMap = Shader->AsSRV("LuminosityMap");
	sBlurResultMap = Shader->AsSRV("BlurResultMap");
}

CBloom::~CBloom()
{
	Delete(CBuffer);

	for (int i = 0; i < 7; i++)
		RenderTargets[i];

	Delete(DepthStencil);
	Delete(Viewport);
}

void CBloom::Tick()
{
	Data.PixelSize.X = 1.0f / CD3D::GetDesc().Width;
	Data.PixelSize.Y = 1.0f / CD3D::GetDesc().Height;


	ImGui::Separator();
	ImGui::SeparatorText("Bloom");

	bool bTemp = bApply;
	ImGui::Checkbox("Bloom Effect", &bTemp);
	
	if (bTemp == true && bApply == false)
	{
		bApply = true;
		Type = EBloomType::ColorGrading;

		bShowGUI = true;
	}
	if (bTemp == false && bApply == true)
	{
		bApply = false;
		Type = EBloomType::Diffuse;

		bShowGUI = false;
	}	

	ImGui::Checkbox("Show Bloom Window", &bShowGUI);
	CheckFalse(bShowGUI);


	ImGui::Begin("Bloom", &bShowGUI);

	ImGui::InputInt("Blur Type", (int*)&Type);
	Type = (EBloomType)FMath::Clamp<UINT>((UINT)Type, 0, (UINT)EBloomType::Max - 1);

	
	ImGui::Separator();
	ImGui::SeparatorText("Luminosity");
	ImGui::InputFloat("Threshold", &Data.Threshold, 0.01f);
	
	
	ImGui::Separator();
	ImGui::SeparatorText("GaussianBlur");	
	ImGui::InputInt("SamplingCount", (int*)&Data.SamplingCount);
	Data.SamplingCount = FMath::Clamp<int>(Data.SamplingCount, 1, 6);

	
	ImGui::Separator();
	ImGui::SeparatorText("ColorGrading");
	ImGui::ColorEdit3("Grade Color", Data.GradeColor);

	ImGui::InputFloat("Grade Amount", &Data.Amount, 0.05f);
	Data.Amount = FMath::Clamp<float>(Data.Amount, 0.0f, 1.0f);

	ImGui::InputFloat("Correlation", &Data.Correlation, 0.05f);
	Data.Correlation = FMath::Clamp<float>(Data.Correlation, 0.0f, 1.0f);

	ImGui::InputFloat("Concentration", &Data.Concentration, 0.05f);
	Data.Concentration = FMath::Clamp<float>(Data.Concentration, 0.0f, 2.0f);
	
	ImGui::End();
	Super::Tick();
}

void CBloom::Begin_PreRender()
{
	assert(bBegin == false);
	bBegin = true;

	RenderTargets[0]->OMSetRenderTarget(DepthStencil);
	RenderTargets[0]->ClearRenderTarget();
	DepthStencil->ClearDepthStencil();
	Viewport->RSSetViewport();
}

void CBloom::End_PreRender()
{
	assert(bBegin == true);
	bBegin = false;

	CheckFalse(bApply);


	//Luminosity
	{
		RenderTargets[1]->OMSetRenderTarget(DepthStencil);
		RenderTargets[1]->ClearRenderTarget();
		DepthStencil->ClearDepthStencil();
		Viewport->RSSetViewport();

		sBloomMap->SetResource(*RenderTargets[0]);

		Render(1);
	}

	//GaussianBlurMRT
	{
		CRenderTarget* rtvs[2];
		rtvs[0] = RenderTargets[2];
		rtvs[1] = RenderTargets[3];

		CRenderTarget::SetRenderTargets(rtvs, 2, DepthStencil);
		RenderTargets[2]->ClearRenderTarget();
		RenderTargets[3]->ClearRenderTarget();
		DepthStencil->ClearDepthStencil();
		Viewport->RSSetViewport();

		sBloomMap->SetResource(*RenderTargets[1]);

		Render(2);
	}

	//GaussianBlurCombiend
	{
		RenderTargets[4]->OMSetRenderTarget(DepthStencil);
		RenderTargets[4]->ClearRenderTarget();
		DepthStencil->ClearDepthStencil();
		Viewport->RSSetViewport();

		ID3D11ShaderResourceView* srvs[2];
		srvs[0] = *RenderTargets[2];
		srvs[1] = *RenderTargets[3];

		sGaussianBlurMaps->SetResourceArray(srvs, 0, 2);

		Render(3);
	}

	//Composite
	{
		RenderTargets[5]->OMSetRenderTarget(DepthStencil);
		RenderTargets[5]->ClearRenderTarget();
		DepthStencil->ClearDepthStencil();

		sLuminosityMap->SetResource(*RenderTargets[1]);
		sBlurResultMap->SetResource(*RenderTargets[4]);

		Render(4);
	}

	//Color Grading
	{
		RenderTargets[6]->OMSetRenderTarget(DepthStencil);
		RenderTargets[6]->ClearRenderTarget();
		DepthStencil->ClearDepthStencil();

		sBloomMap->SetResource(*RenderTargets[5]);
		
		Render(5);
	}
}

void CBloom::Render()
{
	CBuffer->Render();

	//최종결과 : ColorGrading 
	//나머지는 중간 결과 확인을 위함.
	switch (Type)
	{
		case EBloomType::Diffuse: sBloomMap->SetResource(*RenderTargets[0]); break;
		case EBloomType::Luminosity: sBloomMap->SetResource(*RenderTargets[1]); break;
		case EBloomType::GaussianBlurCombiend: sBloomMap->SetResource(*RenderTargets[4]); break;
		case EBloomType::Composite: sBloomMap->SetResource(*RenderTargets[5]); break;
		case EBloomType::ColorGrading: sBloomMap->SetResource(*RenderTargets[6]); break;
	}

	Render(0);
}

void CBloom::Render(UINT InPass)
{
	Super::Render();

	IA_TRIANGLESTRIP();

	Shader->SetPassNumber(InPass);
	Shader->Draw(4);
}
