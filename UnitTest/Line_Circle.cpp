#include "Pch.h"
#include "Line_Circle.h"

void Line_Circle::Initialize()
{
	Shader = new CShader(L"04_Line_Circle.fx");

	float aspectRatio = (float)CD3D::GetDesc().Width/(float)CD3D::GetDesc().Height;

	for (int i = 0; i <= 360; i++)
	{
		float radian = FMath::ToRadians((float)i);

		float x = cos(radian) / aspectRatio;
		float y = -sin(radian); 

		Verticies.push_back({ FVector(x, y, 0.0f), FColor((float)i/ 360.0f, 0.0f, 1.0f, 1.0f) });
	}


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

void Line_Circle::Destroy()
{
	Release(VertexBuffer);
	Delete(Shader);
}

void Line_Circle::Tick()
{

}

void Line_Circle::Render()
{
	UINT stride = sizeof(FVertexColor);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	//CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Shader->Draw(Verticies.size(), 0);
}
