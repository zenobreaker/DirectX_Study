#include "Pch.h"
#include "Line.h"

#include "Framework.h"
#include "Renders/Shader.h"

void Line::Initialize()
{
	//Shader = new CShader(L"04_Line.fx");
	Shader = new CShader(L"04_Line2.fx");

	Verticies.push_back({ FVector(0.0f, +0.5f, 0.0f), FColor(1.0f, 0.0f, 0.0f, 1.0f) });
	Verticies.push_back({ FVector(1.0f, +0.5f, 0.0f), FColor(0.0f, 0.0f, 1.0f, 1.0f) });

	Verticies.push_back({ FVector(0.0f, 0.0f, 0.0f), FColor(0.0f, 1.0f, 0.0f, 1.0f) });
	Verticies.push_back({ FVector(1.0f, 0.0f, 0.0f), FColor(0.0f, 0.0f, 1.0f, 1.0f) });

	Verticies.push_back({ FVector(0.0f, -0.5f, 0.0f), FColor(0.0f, 0.0f, .0f, 1.0f) });
	Verticies.push_back({ FVector(1.0f, -0.5f, 0.0f), FColor(2.0f, 0.0f, 0.0f, 1.0f) });


	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(FVertexColor) * Verticies.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

	FVertexColor* temp = new FVertexColor[Verticies.size()];
	copy(Verticies.begin(), Verticies.end(), temp);
	subResource.pSysMem = temp;

	CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer);

	DeleteArray(temp);
}

void Line::Destroy()
{
	Release(VertexBuffer);
	Delete(Shader);
}

void Line::Tick()
{

}

void Line::Render()
{
	UINT stride = sizeof(FVertexColor);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Shader->Draw(Verticies.size(), 0);
}
