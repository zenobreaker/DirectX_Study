#include "Framework.h"
#include "Blur.h"

CBlur::CBlur()
	: CRenderer(L"00_Blur.fxo")
{
	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	for (int i = 0; i < 4; i++)
		RenderTargets[i] = new CRenderTarget(width, height);

	DepthStencil = new CDepthStencil(width, height);
	Viewport = new CViewport(width, height);


	FVertex vertices[4];
	vertices[0].Position = FVector(-1.0f, -1.0f, 0.0f);
	vertices[1].Position = FVector(-1.0f, +1.0f, 0.0f);
	vertices[2].Position = FVector(+1.0f, -1.0f, 0.0f);
	vertices[3].Position = FVector(+1.0f, +1.0f, 0.0f);

	VBuffer = new CVertexBuffer(vertices, 4, sizeof(FVertex));
	CBuffer = new CConstantBuffer(Shader, "CB_Blur", &Data, sizeof(FDesc));

	sBlurMap = Shader->AsSRV("BlurMap");
	sGaussianBlurMaps = Shader->AsSRV("GaussianBlurMaps");
}

CBlur::~CBlur()
{
	Delete(CBuffer);

	for (int i = 0; i < 4; i++)
		Delete(RenderTargets[i]);

	Delete(DepthStencil);
	Delete(Viewport);
}

void CBlur::Tick()
{
	Data.PixelSize.X = 1.0f / CD3D::GetDesc().Width;
	Data.PixelSize.Y = 1.0f / CD3D::GetDesc().Height;


	ImGui::Separator();
	ImGui::SeparatorText("Blur");
	ImGui::Checkbox("Show Blur Window", &bShowGUI);

	ImGui::InputInt("Blur Type", (int*)&Type);
	Type = (EBlurType)FMath::Clamp<UINT>((UINT)Type, 0, (UINT)EBlurType::Max - 1);

	CheckFalse(bShowGUI);


	ImGui::Begin("Blur", &bShowGUI);

	//PS_Blur
	{
		ImGui::InputInt("Count Blur", (int*)&Data.Count);
		Data.Count = Data.Count < 1 ? 1 : Data.Count;
	}

	//PS_RadialBlur
	{
		ImGui::Separator();
		ImGui::SeparatorText("Radial Blur");

		ImGui::InputFloat("Radius", &Data.Radius, 0.01f);
		ImGui::InputFloat("Amount", &Data.Amount, 0.001f);

		ImGui::InputFloat("CenterX", &Data.Center.X, 0.01f);
		ImGui::InputFloat("CenterY", &Data.Center.Y, 0.01f);
	}

	//PS_PS_GaussianBlur
	{
		ImGui::Separator();
		ImGui::SeparatorText("Gaussian Blur");

		ImGui::InputInt("GaussianCount Blur", (int*)&Data.GaussianCount);
		Data.GaussianCount = FMath::Clamp<UINT>(Data.GaussianCount, 0, 6);
	}

	ImGui::End();
	Super::Tick();
}

void CBlur::Begin_PreRender()
{
	assert(bBegin == false);
	bBegin = true;

	RenderTargets[0]->OMSetRenderTarget(DepthStencil);
	RenderTargets[0]->ClearRenderTarget();
	DepthStencil->ClearDepthStencil();
	Viewport->RSSetViewport();
}

void CBlur::End_PreRender()
{
	assert(bBegin == true);
	bBegin = false;


	switch (Type)
	{
		case EBlurType::GaussianBlur:
		{
			//GaussianBlurX
			{
				RenderTargets[1]->OMSetRenderTarget(DepthStencil);
				RenderTargets[1]->ClearRenderTarget();
				DepthStencil->ClearDepthStencil();
				Viewport->RSSetViewport();

				sBlurMap->SetResource(*RenderTargets[0]);

				Render(3);
			}

			//GaussianBlurX
			{
				RenderTargets[2]->OMSetRenderTarget(DepthStencil);
				RenderTargets[2]->ClearRenderTarget();
				DepthStencil->ClearDepthStencil();
				Viewport->RSSetViewport();

				sBlurMap->SetResource(*RenderTargets[1]);

				Render(4);
			}
		}//case EBlurType::GaussianBlur:

		case EBlurType::GaussianBlurMRT:
		{
			//GaussianBlurMRT
			{
				CRenderTarget* rtvs[2];
				rtvs[0] = RenderTargets[1];
				rtvs[1] = RenderTargets[2];

				CRenderTarget::SetRenderTargets(rtvs, 2, DepthStencil);
				RenderTargets[1]->ClearRenderTarget();
				RenderTargets[2]->ClearRenderTarget();
				DepthStencil->ClearDepthStencil();
				Viewport->RSSetViewport();

				sBlurMap->SetResource(*RenderTargets[0]);

				Render(5);
			}

			//GaussianBlurCombiend
			{
				RenderTargets[3]->OMSetRenderTarget(DepthStencil);
				RenderTargets[3]->ClearRenderTarget();
				DepthStencil->ClearDepthStencil();
				Viewport->RSSetViewport();

				ID3D11ShaderResourceView* srvs[2];
				srvs[0] = *RenderTargets[1];
				srvs[1] = *RenderTargets[2];

				sGaussianBlurMaps->SetResourceArray(srvs, 0, 2);

				Render(6);
			}
		}//case EBlurType::GaussianBlur:
	}
}

void CBlur::Render()
{
	CBuffer->Render();

	switch (Type)
	{
		case EBlurType::Diffuse:
		{
			sBlurMap->SetResource(*RenderTargets[0]);
			Render(0);
		}
		break;

		case EBlurType::Blur:
		{
			sBlurMap->SetResource(*RenderTargets[0]);
			Render(1);
		}
		break;

		case EBlurType::RadialBlur:
		{
			sBlurMap->SetResource(*RenderTargets[0]);
			Render(2);
		}
		break;

		case EBlurType::GaussianBlur:
		{
			sBlurMap->SetResource(*RenderTargets[2]);
			Render(0);
		}
		break;

		case EBlurType::GaussianBlurMRT:
		{
			sBlurMap->SetResource(*RenderTargets[3]);
			Render(0);
		}
		break;
	}
}

void CBlur::Render(UINT InPass)
{
	Super::Render();

	IA_TRIANGLESTRIP();

	Shader->SetPassNumber(InPass);
	Shader->Draw(4);
}