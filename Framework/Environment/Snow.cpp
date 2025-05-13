#include "Framework.h"
#include "Snow.h"

CSnow::CSnow(const FVector& InExtent, UINT InDrawCount)
	: CRenderer(L"00_Weather.fxo")
	, DrawCount(InDrawCount)
{
	Data.Extent = InExtent;
	Data.DrawDistance = Data.Extent.Z * 2.0f;

	Texture = new CTexture(Shader, "WeatherMap", L"Environments/Snow.png");
	CBuffer = new CConstantBuffer(Shader, "CB_Weather", &Data, sizeof(FDesc));

	FVertexSnow* vertices = new FVertexSnow[DrawCount];

	for (UINT i = 0; i < DrawCount; i++)
	{
		FVector2D scale = FVector2D(FMath::Random(0.05f, 0.2f));

		FVector position;
		position.X = FMath::Random(-Data.Extent.X, +Data.Extent.X);
		position.Y = FMath::Random(-Data.Extent.Y, +Data.Extent.Y);
		position.Z = FMath::Random(-Data.Extent.Z, +Data.Extent.Z);

		FVector2D random;
		random.X = FMath::Random(0.0f, 1.0f);
		random.Y = FMath::Random(0.0f, 1.0f);

		vertices[i].Position = position;
		vertices[i].Scale = scale;
		vertices[i].Random = random;
	}

	VBuffer = new CVertexBuffer(vertices, DrawCount, sizeof(FVertexSnow));
	DeleteArray(vertices);
}

CSnow::~CSnow()
{
	Delete(CBuffer);
	Delete(Texture);
}

void CSnow::Tick()
{
	ImGui::SeparatorText("Snow");

	//Settings.Origin = Context::Get()->GetCamera()->GetPosition();
	ImGui::Separator();
	ImGui::InputFloat("OriginX Snow", &Data.Origin.X);
	ImGui::InputFloat("OriginY Snow", &Data.Origin.Y);
	ImGui::InputFloat("OriginZ Snow", &Data.Origin.Z);

	ImGui::Separator();
	ImGui::InputFloat("VelocityX Snow", &Data.Velocity.X, 0.1f);
	ImGui::InputFloat("VelocityY Snow", &Data.Velocity.Y, 0.1f);
	ImGui::InputFloat("VelocityZ Snow", &Data.Velocity.Z, 0.1f);

	ImGui::InputFloat("Turbulence Snow", &Data.Turbulence, 0.1f);

	ImGui::InputFloat("Distance Snow", &Data.DrawDistance);
	Data.DrawDistance = FMath::Clamp<float>(Data.DrawDistance, 0, Data.Extent.Z * 2.0f);

	ImGui::ColorEdit3("Color Snow", Data.Color);


	Super::Tick();
}

void CSnow::Render()
{
	Super::Render();

	CBuffer->Render();
	Texture->Render();


	IA_POINTLIST();

	Shader->SetPassNumber(1);
	Shader->Draw(DrawCount);
}
