#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(12.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(71.0f, 24.0f, -10.0f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	MaterialFolder = L"";
	ShaderFile = L"TerrainNormal.fx";

	CreateTerrain(); 
	CreateCube();
}

void CDemo::Destroy()
{
	Delete(Terrain); 

	Delete(Cube);
}

void CDemo::Tick()
{
	Terrain->Tick(); 

	Cube->Tick();
}

void CDemo::PreRender()
{
	
}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	Terrain->SetPass(Pass);
	Terrain->Render();

	Cube->Render(); 
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

void CDemo::CreateCube()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	Cube = new CMeshRender(Shader);
	Cube->ReadMaterial(MaterialFolder + L"Cube");
	Cube->AddMaterial(L"Box");
	Cube->ReadMesh(L"Cube");


	CTransform* t = Cube->AddTransform();
	t->SetPosition(FVector(100.5f , 11.5f , 64.0f ));
	t->SetScale(100.0f);
	t->UpdateWorld();
}
