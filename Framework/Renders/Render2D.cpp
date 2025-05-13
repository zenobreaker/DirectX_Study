#include "Framework.h"
#include "Render2D.h"

CRender2D::CRender2D(ID3D11ShaderResourceView* InSRV)
	: CRenderer(L"00_Render2D.fxo")
{
	Data.View = FMatrix::CreateLookAt(FVector(0, 0, -1), FVector::Zero, FVector::Up);


	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	Data.Projection = FMatrix::CreateOrthographicOffCenter(0.0f, width, 0.0f, height, -1.0f, +1.0f);


	FVertexTexture vertices[4];

	vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = FVector2D(0, 1);
	vertices[1].Uv = FVector2D(0, 0);
	vertices[2].Uv = FVector2D(1, 1);
	vertices[3].Uv = FVector2D(1, 0);


	VBuffer = new CVertexBuffer(vertices, 4, sizeof(FVertexTexture));
	Shader->AsSRV("Render2DMap")->SetResource(InSRV);

	CBuffer = new CConstantBuffer(Shader, "CB_Render2D", &Data, sizeof(FDesc));
}

CRender2D::~CRender2D()
{
	Delete(CBuffer);
}

void CRender2D::Tick()
{
	Super::Tick();
}

void CRender2D::Render()
{
	Super::Render();

	CBuffer->Render();
	IA_TRIANGLESTRIP();

	Shader->Draw(4);
}
