#include "Pch.h"
#include "Triangle_List.h"

void Triangle_List::Initialize()
{
	Shader = new CShader(L"Triangle.fx");

	Verticies.clear();
	{

		Verticies.push_back({ FVector(-0.5f, +0.0f, 0.0f), FColor(1,0,0,1) });
		Verticies.push_back({ FVector(+0.0f, +0.5f, 0.0f), FColor(0,0,1,1) });
		Verticies.push_back({ FVector(+0.5f, +0.0f, 0.0f), FColor(0,1,0,1) });


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

	Verticies.clear();
	{

		Verticies.push_back({ FVector(-0.5f, -0.2f, 0.0f), FColor(1,0,0,1) });
		Verticies.push_back({ FVector(+0.5f, -0.2f, 0.0f), FColor(0,1,0,1) });
		Verticies.push_back({ FVector(+0.0f, -0.7f, 0.0f), FColor(0,0,1,1) });


		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(FVertexColor) * Verticies.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource;
		ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

		FVertexColor* temp = new FVertexColor[Verticies.size()];
		copy(Verticies.begin(), Verticies.end(), temp);
		subResource.pSysMem = temp;

		CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer2);

		DeleteArray(temp);
	}
}

void Triangle_List::Destroy()
{
	Release(VertexBuffer);
	Delete(Shader);
}

void Triangle_List::Tick()
{

}

void Triangle_List::Render()
{
	UINT stride = sizeof(FVertexColor);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	Shader->SetPassNumber(0);
	Shader->Draw(Verticies.size(), 0);

	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer2, &stride, &offset);
	Shader->SetPassNumber(1);
	Shader->Draw(Verticies.size(), 0);
}
