#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(12.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(71.0f, 24.0f, -10.0f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	ShaderFile = L"TerrainNormal.fx";

	CreateTerrain(); 
}

void CDemo::Destroy()
{
	Delete(Terrain); 
}

void CDemo::Tick()
{
	Terrain->Tick(); 
}

void CDemo::PreRender()
{
	
}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	Terrain->SetPass(Pass);
	Terrain->Render();
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
