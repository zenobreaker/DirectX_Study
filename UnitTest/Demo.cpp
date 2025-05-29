#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(12.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(71.0f, 24.0f, -10.0f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	ShaderFile = L"TerrainNormal.fx";

	CreateTerrain(); 

	Shader = new CShader(L"TerrainDebugLine.fx");

	World = FMatrix::Identity;
	CTerrain::FVertexTerrain* vertices = Terrain->GetVerticies(); 
	UINT width = Terrain->GetWidth(); 
	UINT height = Terrain->GetHeight(); 

	for (UINT  z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			UINT index = width * z + x; 

			FVector start = vertices[index].Position;
			FVector end = vertices[index].Position + vertices[index].Normal * 2; 

			Vertices.push_back(FVertexColor(start, FColor::Green));
			Vertices.push_back(FVertexColor(end, FColor::Green));
		}
	}

	FVertexColor* vert2 = new FVertexColor[Vertices.size()];
	copy(Vertices.begin(), Vertices.end(), vert2);

	VBuffer = new CVertexBuffer(vert2, Vertices.size(), sizeof(FVertexColor));

	DeleteArray(vert2);
}

void CDemo::Destroy()
{
	Delete(VBuffer);
	Delete(Shader); 
	Delete(Terrain); 
}

void CDemo::Tick()
{
	Terrain->Tick(); 

	Shader->AsMatrix("World")->SetMatrix(World);
	Shader->AsMatrix("View")->SetMatrix(CContext::Get()->GetViewMatrix());
	Shader->AsMatrix("Projection")->SetMatrix(CContext::Get()->GetProjectionMatrix());
}

void CDemo::PreRender()
{
}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	Terrain->SetPass(Pass);
	Terrain->Render();

	IA_LINELIST();
	VBuffer->Render();
	Shader->Draw(Vertices.size());
}

void CDemo::PostRender()
{

}

void CDemo::CreateTerrain()
{
	Terrain = new CTerrain(L"Terrain/Gray256.png", ShaderFile);
	Terrain->SetBaseMap(L"Terrain/Sand.png", L"Terrain/Sand_Normal.png");
	Terrain->SetLowMap(L"Terrain/Grass.png", L"Terrain/Grass_Normal.png");
	Terrain->SetHighMap(L"Terrain/Grass2.png", L"Terrain/Grass2_Normal.png");
	Terrain->SetSlopeMap(L"Terrain/Rock.png", L"Terrain/Rock_Normal.png");
}
