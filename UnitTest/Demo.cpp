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
	
	//CreateCube();
	//CreateSphere();
	//CreateAirplane();

	//CreateKachujin();
	CreateKachujin_Old();
}

void CDemo::Destroy()
{
	Delete(Terrain); 

	for(auto& render : Renders)
		Delete(render); 
}

void CDemo::Tick()
{
	Terrain->Tick(); 
	ImGui::Separator();
	ImGui::SeparatorText("Render Pass");
	static int pass = 0;
	ImGui::SliderInt("Pass", (int*)&pass, 0, 1);

	for (int i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetPass((UINT)pass);
		Renders[i]->Tick();
	}

	if (BoneDebugger != nullptr)
		BoneDebugger->Tick();
}

void CDemo::PreRender()
{
	
}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	Terrain->SetPass(Pass);
	Terrain->Render();

	for (int i = 0; i < Renders.size(); i++)
	{
		Renders[i]->Render();
	}

	if(BoneDebugger != nullptr)
		BoneDebugger->Render();
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
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Cube");
	render->AddMaterial(L"Box");
	render->ReadMesh(L"Cube");


	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f , 11.5f , 64.0f ));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);
}

void CDemo::CreateAirplane()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Airplane");
	render->ReadMesh(L"Airplane");


	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f, 11.5f, 64.0f));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);	

	DrawModelBone(render);
}

void CDemo::CreateSphere()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Sphere");
	render->ReadMesh(L"Sphere");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f, 11.5f, 64.0f));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);
}

void CDemo::CreateKachujin()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Kachujin");
	render->ReadMesh(L"Kachujin/Kachujin");
	render->ReadAnimation(L"Kachujin/Idle");
	render->Finish_ReadDatas(); 

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f, 11.5f, 64.0f));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);
	DrawModelBone(render);
}

void CDemo::CreateKachujin_Old()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Kachujin_Old");
	render->ReadMesh(L"Kachujin_Old/Kachujin_Old");
	render->ReadAnimation(L"Kachujin_Old/Idle");
	render->Finish_ReadDatas();

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f, 11.5f, 64.0f));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::DrawModelBone(CMeshRender* InMesh)
{
	CShader* shader = CShaders::Get()->GetShader(L"Sphere.fx");
	BoneDebugger = new CSphereDebugDrawer(shader, InMesh);
}
