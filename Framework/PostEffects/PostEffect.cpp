#include "Framework.h"
#include "PostEffect.h"

CPostEffect::CPostEffect()
	: CRenderer(L"00_PostEffect.fxo")
{
	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	RenderTarget = new CRenderTarget(width, height);
	Shader->AsSRV("PostEffectMap")->SetResource(*RenderTarget);

	DepthStencil = new CDepthStencil(width, height);

	CBuffer = new CConstantBuffer(Shader, "CB_PostEffect", &Data, sizeof(FDesc));


	FVertex vertices[4];
	vertices[0].Position = FVector(-1.0f, -1.0f, 0.0f);
	vertices[1].Position = FVector(-1.0f, +1.0f, 0.0f);
	vertices[2].Position = FVector(+1.0f, -1.0f, 0.0f);
	vertices[3].Position = FVector(+1.0f, +1.0f, 0.0f);

	VBuffer = new CVertexBuffer(vertices, 4, sizeof(FVertex));

	Data.BlurSourceScale.X = CD3D::GetDesc().Width;
	Data.BlurSourceScale.Y = CD3D::GetDesc().Height;
}

CPostEffect::~CPostEffect()
{
	Delete(CBuffer);

	Delete(RenderTarget);
	Delete(DepthStencil);
}

void CPostEffect::Tick()
{
	Data.PixelSize.X = 1.0f / CD3D::GetDesc().Width;
	Data.PixelSize.Y = 1.0f / CD3D::GetDesc().Height;


	ImGui::Separator();
	ImGui::SeparatorText("PostEffect");
	ImGui::Checkbox("Show PostEffect Window", &bShowGUI);

	ImGui::InputInt("PostEffect Type", (int*)&Type);
	Type = (EPostEffectType)FMath::Clamp<UINT>((UINT)Type, 0, (UINT)EPostEffectType::Max - 1);

	CheckFalse(bShowGUI);


	ImGui::Begin("PostEffect", &bShowGUI);

	//Saturation
	{
		ImGui::Separator();
		ImGui::SeparatorText("Saturation");

		ImGui::InputFloat("Saturation", &Data.Saturation, 0.1f);
	}

	//Sharpness
	{
		ImGui::Separator();
		ImGui::SeparatorText("Sharpness");

		ImGui::InputFloat("Sharpness", &Data.Sharpness, 0.1f);
	}

	//Vignette
	{
		ImGui::Separator();
		ImGui::SeparatorText("Vignette");

		ImGui::InputFloat("VignettePower", &Data.VignettePower, 0.1f);

		ImGui::InputFloat("VignetteScaleX", &Data.VignetteScale.X, 0.1f);
		ImGui::InputFloat("VignetteScaleY", &Data.VignetteScale.Y, 0.1f);
	}

	//LensDistortion
	{
		ImGui::Separator();
		ImGui::SeparatorText("LensDistortion");

		ImGui::InputFloat("LensPower", &Data.LensPower, 0.025f);

		ImGui::InputFloat("LensDistortionX", &Data.LensDistortion.X, 0.001f);
		ImGui::InputFloat("LensDistortionY", &Data.LensDistortion.Y, 0.001f);
		ImGui::InputFloat("LensDistortionZ", &Data.LensDistortion.Z, 0.001f);
	}

	//Interace
	{
		ImGui::Separator();
		ImGui::SeparatorText("Interace");

		ImGui::InputFloat("InteraceStrength", &Data.InteraceStrength, 0.01f);
		ImGui::InputInt("InteraceValue", &Data.InteraceValue);
	}

	//Wiggle
	{
		ImGui::Separator();
		ImGui::SeparatorText("Wiggle");

		ImGui::InputFloat("WiggleOffsetX", &Data.WiggleOffset.X, 0.1f);
		ImGui::InputFloat("WiggleOffsetY", &Data.WiggleOffset.Y, 0.1f);

		ImGui::InputFloat("WiggleAmountX", &Data.WiggleAmount.X, 0.001f);
		ImGui::InputFloat("WiggleAmountY", &Data.WiggleAmount.Y, 0.001f);
	}

	//Blur
	{
		ImGui::Separator();
		ImGui::SeparatorText("Blur");

		ImGui::InputFloat("BlurSourceScaleX", &Data.BlurSourceScale.X, 1.0f);
		ImGui::InputFloat("BlurSourceScaleY", &Data.BlurSourceScale.Y, 1.0f);
	}


	ImGui::End();

	Super::Tick();
}

void CPostEffect::PreRender()
{
	RenderTarget->OMSetRenderTarget(DepthStencil);
	RenderTarget->ClearRenderTarget();
	DepthStencil->ClearDepthStencil();
}

void CPostEffect::Render()
{
	Super::Render();

	CBuffer->Render();

	IA_TRIANGLESTRIP();

	Shader->SetPassNumber((UINT)Type);
	Shader->Draw(4);
}
