#include "Pch.h"
#include "Line.h"

void Line::Initialize()
{
	shader = new Shader(L"04_Line.fx");

	Verticies[0] = Vector(0.0f, 0.0f, 0.0f);
	Verticies[1] = Vector(1.0f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vector) * 2;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = Verticies;

	D3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer);
}

void Line::Destroy()
{
	Release(VertexBuffer);
	Delete(shader);
}

void Line::Tick()
{

}

void Line::Render()
{
	UINT stride = sizeof(Vector);
	UINT offset = 0;
	D3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	D3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 0, 2); 
}
