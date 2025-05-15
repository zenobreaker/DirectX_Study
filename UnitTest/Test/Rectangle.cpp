#include "Pch.h"
#include "Rectangle.h"

const int CRectangle::VertexCount = 6;

void CRectangle::Initialize()
{
	Shader = new CShader(L"Rect.fx");

	Verticies = new FVertex[VertexCount];

	Verticies[0].Position = FVector(+0.0f, +0.0f, +0.0f);
	Verticies[1].Position = FVector(+0.0f, +0.5f, +0.0f);
	Verticies[2].Position = FVector(+0.5f, +0.0f, +0.0f);
	
	Verticies[3].Position = FVector(+0.5f, +0.0f, +0.0f);
	Verticies[4].Position = FVector(+0.0f, +0.5f, +0.0f);
	Verticies[5].Position = FVector(+0.5f, +0.5f, +0.0f);


	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(FVertex) * VertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

	subResource.pSysMem = Verticies;
	CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer);
}

void CRectangle::Destroy()
{
	DeleteArray(Verticies);
	Release(VertexBuffer);
	Delete(Shader);
}

void CRectangle::Tick()
{

}

void CRectangle::Render()
{
	UINT stride = sizeof(FVertex);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Shader->SetPassNumber(1);
	Shader->Draw(VertexCount, 0);
	
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	Shader->SetPassNumber(0);
	Shader->Draw(VertexCount, 0);
}
