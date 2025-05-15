#include "Pch.h"
#include "Demo.h"

const  int CDemo::VertexCount = 4;
const  int CDemo::IndexCount = 6;

void CDemo::Initialize()
{
	Shader = new CShader(L"World.fx");

	Vertices = new FVertex[VertexCount];

	Vertices[0].Position = FVector(-0.5f, -0.5f, +0.0f);
	Vertices[1].Position = FVector(-0.5f, +0.5f, +0.0f);
	Vertices[2].Position = FVector(+0.5f, -0.5f, +0.0f);
	Vertices[3].Position = FVector(+0.5f, +0.5f, +0.0f);


	// Vertex Buffer 
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(FVertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource;
		ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

		subResource.pSysMem = Vertices;
		CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer);

	}

	Indices = new UINT[IndexCount]
	{
		0,1,2,2,1,3
	};

	//Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * IndexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource;
		ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

		subResource.pSysMem = Indices;
		CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &IndexBuffer);
	}

	
	World = FMatrix::Identity;


	FVector position(0, 0, -10);
	FVector forward(0, 0, 1); 
	FVector right(1, 0, 0);
	FVector up(0, 1, 0);

	View = FMatrix::CreateLookAt(position, (position + forward), up);

	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * 0.25f, width / height, 0.1f, 1000.f);
}

void CDemo::Destroy()
{
	DeleteArray(Vertices);
	DeleteArray(Indices);
	
	Release(VertexBuffer);
	Release(IndexBuffer);

	Delete(Shader);
}

void CDemo::Tick()
{
	static FVector2D location(0, 0);
	static FVector2D scale(1, 1);
	ImGui::SliderFloat2("Location", location, -5, +5);


	if (CKeyboard::Get()->Press(VK_LEFT))
		location.X -= 1.0f * CTimer::Get()->GetDeltaTime(); 
	
	if (CKeyboard::Get()->Press(VK_RIGHT))
		location.X += 1.0f * CTimer::Get()->GetDeltaTime();

	if(CKeyboard::Get()->Press(VK_UP))
		location.Y += 1.0f * CTimer::Get()->GetDeltaTime();
	if(CKeyboard::Get()->Press(VK_DOWN))
		location.Y -= 1.0f * CTimer::Get()->GetDeltaTime();

	if (CKeyboard::Get()->Press('Z'))
		scale.X += 1.0f * CTimer::Get()->GetDeltaTime();
	if (CKeyboard::Get()->Press('X'))
		scale.X -= 1.0f * CTimer::Get()->GetDeltaTime();

	if (CKeyboard::Get()->Press('C'))
		scale.Y += 1.0f * CTimer::Get()->GetDeltaTime();
	if (CKeyboard::Get()->Press('V'))
		scale.Y -= 1.0f * CTimer::Get()->GetDeltaTime();

	World.M11 = scale.X;
	World.M22 = scale.Y;

	World.M41 = location.X;
	World.M42 = location.Y;
}

void CDemo::PreRender()
{
	
}

void CDemo::Render()
{
	Shader->AsMatrix("World")->SetMatrix(World);
	Shader->AsMatrix("View")->SetMatrix(View);
	Shader->AsMatrix("Projection")->SetMatrix(Projection);

	UINT stride = sizeof(FVertex);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	Shader->SetPassNumber(0);
	Shader->DrawIndexed(IndexCount, 0, 0);
}

void CDemo::PostRender()
{
	
}
 