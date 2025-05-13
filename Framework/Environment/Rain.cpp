#include "Framework.h"
#include "Rain.h"

CRain::CRain(const FVector& InExtent, UINT InDrawCount)
	: CRenderer(L"00_Weather.fxo")
	, DrawCount(InDrawCount)
{
	Data.Extent = InExtent;
	Data.DrawDistance = Data.Extent.Z * 2.0f;

	Texture = new CTexture(Shader, "WeatherMap", L"Environments/Rain.png");
	CBuffer = new CConstantBuffer(Shader, "CB_Weather", &Data, sizeof(FDesc));
	
	FVertexRain* vertices = new FVertexRain[DrawCount];

	for (UINT i = 0; i < DrawCount; i++)
	{
		FVector2D scale;
		scale.X = FMath::Random(0.05f, 0.2f);
		scale.Y = FMath::Random(1.0f, 4.0f);

		FVector position;
		position.X = FMath::Random(-Data.Extent.X, +Data.Extent.X);
		position.Y = FMath::Random(-Data.Extent.Y, +Data.Extent.Y);
		position.Z = FMath::Random(-Data.Extent.Z, +Data.Extent.Z);


		vertices[i].Position = position;
		vertices[i].Scale = scale;
	}

	VBuffer = new CVertexBuffer(vertices, DrawCount, sizeof(FVertexRain));
	DeleteArray(vertices);
}

CRain::~CRain()
{
	Delete(CBuffer);
	Delete(Texture);
}

void CRain::Tick()
{
	ImGui::SeparatorText("Rain");

	//Settings.Origin = Context::Get()->GetCamera()->GetPosition();
	ImGui::Separator();
	ImGui::InputFloat("OriginX Rain", &Data.Origin.X);
	ImGui::InputFloat("OriginY Rain", &Data.Origin.Y);
	ImGui::InputFloat("OriginZ Rain", &Data.Origin.Z);

	ImGui::Separator();
	ImGui::InputFloat("VelocityX Rain", &Data.Velocity.X, 0.1f);
	ImGui::InputFloat("VelocityY Rain", &Data.Velocity.Y, 0.1f);
	ImGui::InputFloat("VelocityZ Rain", &Data.Velocity.Z, 0.1f);

	ImGui::InputFloat("Distance Rain", &Data.DrawDistance);
	Data.DrawDistance = FMath::Clamp<float>(Data.DrawDistance, 0, Data.Extent.Z * 2.0f);
	
	ImGui::ColorEdit3("Color Rain", Data.Color);
	

	Super::Tick();
}

void CRain::Render()
{
	Super::Render();

	CBuffer->Render();
	Texture->Render();

	
	IA_POINTLIST();

	Shader->SetPassNumber(0);
	Shader->Draw(DrawCount);
}
