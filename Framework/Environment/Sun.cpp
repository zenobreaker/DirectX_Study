#include "Framework.h"
#include "Sun.h"

CSun::CSun(wstring InShader)
	: CRenderer(InShader)
{
	FVertex vertex;
	vertex.Position = FVector::Zero;

	VBuffer = new CVertexBuffer(&vertex, 1, sizeof(FVertex));
	CBuffer = new CConstantBuffer(Shader, "CB_Sun", &Data, sizeof(FDesc));

	Texture = new CTexture(Shader, "SunMap", L"Environments/Sun.png");
}

CSun::~CSun()
{
	Delete(CBuffer);
	Delete(Texture);
}

void CSun::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Sun");
	ImGui::InputFloat("Scale Sun", &Data.Scale, 1.0f);
	ImGui::InputFloat("PositionX Sun", &PositionX, 0.05f);
	ImGui::InputFloat("AlphaHeightY Sun", &Data.AlphaHeightY, 0.01f);


	FVector cameraPosition = CContext::Get()->GetCamera()->GetPosition();
	FVector lightDirection = CContext::Get()->GetLightDirection();

	
	FVector forward = FVector(0, 0, DrawDistance);

	FVector position;
	position = cameraPosition;
	position.X += PositionX;

	float sunAngle = CContext::Get()->GetSunAngle();
	FMatrix rotation = FMatrix::CreateRotationX(-sunAngle);
	FVector axis = FVector::TransformCoord(forward, rotation);

	position = position + axis;


	Transform->SetPosition(position);
	Transform->UpdateWorld();

	Super::Tick();
}

void CSun::Render()
{
	Super::Render();

	CBuffer->Render();
	Texture->Render();

	IA_POINTLIST();

	Shader->SetPassNumber(3);
	Shader->Draw(1);
}

