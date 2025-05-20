#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(8.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(0.0f, 0.0f, -10.0f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	Shader = new CShader(L"Texture_Layering.fx");


	Vertices = new FVertexTexture[VertexCount];
	Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
	Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
	Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
	Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

	Vertices[0].Uv = FVector2D(0, 1);
	Vertices[1].Uv = FVector2D(0, 0);
	Vertices[2].Uv = FVector2D(1, 1);
	Vertices[3].Uv = FVector2D(1, 0);




	// Vertex Buffer 
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(FVertexTexture) * VertexCount;
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
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * IndexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource;
		ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));

		subResource.pSysMem = Indices;
		CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &IndexBuffer);
	}

	DeleteArray(Vertices);
	DeleteArray(Indices);

	World = FMatrix::Identity;

	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * 0.25f, width / height, 0.1f, 1000.f);

	wstring str[3]; 
	str[0] = L"../../_Textures/Box.png";
	str[1] = L"../../_Textures/Grayscale.png";
	str[2] = L"../../_Textures/Forest Floor.jpg";

	for (int i = 0; i < 3; i++)
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			CD3D::Get()->GetDevice(), str[i].c_str(), nullptr, nullptr, &SRV[i], nullptr
		);
		Check(hr);
	}
}

void CDemo::Destroy()
{
	for (int i = 0; i < 3; i++)
	{
		Release(SRV[i]);
	}

	Release(VertexBuffer);
	Release(IndexBuffer);

	Delete(Shader);
}

void CDemo::Tick()
{
}

void CDemo::PreRender()
{

}

void CDemo::Render()
{
	Shader->AsMatrix("World")->SetMatrix(World);
	Shader->AsMatrix("View")->SetMatrix(CContext::Get()->GetViewMatrix());
	Shader->AsMatrix("Projection")->SetMatrix(Projection);
	
	Shader->AsSRV("Map")->SetResourceArray(SRV,0, 3);

	UINT stride = sizeof(FVertexTexture);
	UINT offset = 0;
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	CD3D::Get()->GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	Shader->DrawIndexed(IndexCount, 0, 0);
}

void CDemo::PostRender()
{

}
