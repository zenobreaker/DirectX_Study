#include "Framework.h"
#include "Sky.h"

CSky::CSky(wstring InTextureFile, wstring InShader, float InScale)
	:Scale(InScale)
{
	Shader = CShaders::Get()->GetShader(InShader);

	Mesh = new CMeshRender(Shader);
	Mesh->ReadMaterial(L"63/Sky");
	Mesh->ReadMesh(L"Sphere");

	Transform = Mesh->AddTransform();
	Transform->SetScale(Scale);
	Transform->SetRotation(FVector(-90, 90, 0));
	Transform->UpdateWorld();

	CBuffer = new CConstantBuffer(Shader, "CB_Sky", &Data, sizeof(FDesc));


	InTextureFile = L"../../_Textures/" + InTextureFile;

	Check(D3DX11CreateShaderResourceViewFromFile
	(
		CD3D::Get()->GetDevice(), InTextureFile.c_str(), nullptr, nullptr, &SRV, nullptr
	));

	sSRV = Shader->AsSRV("SkyCubeMap");
}

CSky::~CSky()
{
	Delete(Mesh);

	Delete(CBuffer);
}

void CSky::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Sky");
	ImGui::InputFloat("HorizonStartY Sky", &Data.HorizonStartY, 0.05f);
	ImGui::InputFloat("Tiling Sky", &Data.Tiling, 0.1f);
	ImGui::InputFloat("StarBrightness Sky", &Data.StarBrightness, 0.25f);
	ImGui::InputFloat("CubeMapAlpha Sky", &Data.CubeMapAlpha, 0.01f);

	ImGui::InputFloat("Sphere Scale", &Scale, 1.0f);
	if (ImGui::Button("Apply Sphere Scale"))
		Transform->SetScale(FVector(Scale));

	FVector position = CContext::Get()->GetCamera()->GetPosition();
	Transform->SetPosition(position);
	Transform->UpdateWorld();

	Mesh->Tick();
}

void CSky::Render()
{
	CBuffer->Render();
	sSRV->SetResource(SRV);

	Mesh->Render();
}



