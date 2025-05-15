#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	Shader = new CShader(L"Grid.fx");

	VertexCount = (Width + 1) * (Height + 1);
	Vertices = new FVertex[VertexCount];

	for (UINT y = 0; y <= Height; y++)
	{
		for (UINT x = 0; x <= Width; x++)
		{
			UINT i = (Width + 1) * y + x;
			Vertices[i].Position.X = (float)x;
			Vertices[i].Position.Y = (float)y;
			Vertices[i].Position.Z = 0;
		}
	}

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

	IndexCount = (Width * Height) * 6;
	Indices = new UINT[IndexCount];

	UINT index = 0;
	for (UINT y = 0; y < Height; y++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			Indices[index + 0] = (Width + 1) * y + x;
			Indices[index + 1] = (Width + 1) * (y + 1) + x;
			Indices[index + 2] = (Width + 1) * y + x + 1;
			Indices[index + 3] = (Width + 1) * y + x + 1;
			Indices[index + 4] = (Width + 1) * (y + 1) + x;
			Indices[index + 5] = (Width + 1) * (y + 1) + x + 1;

			index += 6;
		}
	}

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

	if (CKeyboard::Get()->Press(VK_UP))
		location.Y += 1.0f * CTimer::Get()->GetDeltaTime();
	if (CKeyboard::Get()->Press(VK_DOWN))
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

	static int pass = 0;
	ImGui::SliderInt("Pass", (int*)&pass, 0, 1);

	Shader->SetPassNumber(pass);
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


	Shader->DrawIndexed(IndexCount, 0, 0);
}

void CDemo::PostRender()
{

}
