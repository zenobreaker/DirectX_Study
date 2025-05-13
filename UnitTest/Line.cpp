#include "Pch.h"
#include "Line.h"

#include "Framework.h"
#include "Renders/Shader.h"

void Line::Initialize()
{
	shader = new CShader(L"04_Line.fx");

	Verticies[0] = FVector(0.0f, 0.0f, 0.0f);
	Verticies[1] = FVector(1.0f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(FVector) * 2;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = Verticies;

	CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer);
}

void Line::Destroy()
{
	Release(VertexBuffer);
}

void Line::Tick()
{

}

void Line::Render()
{
	UINT stride = sizeof(FVector);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(2, 1); 
}
