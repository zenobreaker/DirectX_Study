#include "Framework.h"
#include "Billboard.h"

CBillboard::CBillboard(wstring InShader)
	: CRenderer(InShader)
{
	CBuffer = new CConstantBuffer(Shader, "CB_Billboard", &Data, sizeof(FDesc));
}

CBillboard::~CBillboard()
{
	Delete(TextureArray);
	Delete(CBuffer);
}

void CBillboard::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Billboard");

	ImGui::InputInt("Pass Billboard", (int*)&Pass);
	Pass = FMath::Clamp<UINT>(Pass, 5, 6);

	ImGui::InputFloat("Brightnesss Billboard", &Data.Brightness, 0.1f);

	Super::Tick();
}

void CBillboard::Render()
{
	if (TextureNames.size() > 0 && TextureArray == nullptr)
	{
		Delete(TextureArray);

		TextureArray = new CTextureArray(Shader, "BillboardMaps", TextureNames);
	}

	if (VCount != Vertices.size())
	{
		VCount = Vertices.size();

		Delete(VBuffer);
		VBuffer = new CVertexBuffer(&Vertices[0], Vertices.size(), sizeof(FVertexBillboard));
	}
	Super::Render();


	CBuffer->Render();
	TextureArray->Render();

	IA_TRIANGLELIST();

	Shader->SetPassNumber(Pass);
	Shader->Draw(VCount);
}

void CBillboard::AddTexture(wstring InFile)
{
	TextureNames.push_back(InFile);
}

void CBillboard::AddPosition(const FVector& InPosition, const FVector2D& InScale, UINT InMapIndex)
{
	FVertexBillboard vertex = { InPosition, InScale, InMapIndex };

	Vertices.push_back(vertex);
}
