#include "Pch.h"
#include "Demo.h"

void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(30.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(119.0f, 4.31f, 81.43f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	MaterialFolder = L"";
	ShaderFile = L"TerrainNormal.fx";

	CreateTerrain();

	CreateFloor();
	CreateCube();
	//CreateSphere();
	//CreateAirplane();

	CreateKachujin();
	//CreateKachujin_Old();
	CreateTurtle();
}

void CDemo::Destroy()
{
	Delete(Terrain);

	for (auto& render : Renders)
		Delete(render);
}

void CDemo::Tick()
{
	//Terrain->Tick(); 
	ImGui::Separator();
	ImGui::SeparatorText("Render Pass");
	static int pass = 0;
	ImGui::SliderInt("Pass", (int*)&pass, 0, 1);

	ImGui::SeparatorText("Model");
	static int prev = 0;
	ImGui::SliderInt("Model", (int*)&ModelIndex, 0, Renders.size() - 1);


	//static int clipNumber = 0;
	//if (prev != ModelIndex)
	//{
	//	prev = ModelIndex;
	//	clipNumber = 0;
	//}
	//
	//int maxClip = 0;
	//auto ar = dynamic_cast<CAnimRender*>(Renders[ModelIndex]);
	//if (ar != nullptr)
	//{
	//	maxClip = ar->GetAnimationCount();
	//}
	//ImGui::SliderInt("ClipNumber", (int*)&clipNumber, 0, maxClip-1);

	//if (ImGui::Button("Change"))
	//{
	//	if (ar != nullptr)
	//		ar->ChangeClip(0, clipNumber);
	//}


	for (auto render : Renders)
		render->Tick();

	if (BoneDebugger != nullptr)
		BoneDebugger->Tick();
}

void CDemo::PreRender()
{

}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	//Terrain->SetPass(Pass);
	//Terrain->Render();

	for (auto render : Renders)
		render->Render();

	if (BoneDebugger != nullptr)
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

	int index = 0;
	for (float x = -7.0f; x <= 7.0; x += 0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z - 0.5f));
		float rotX = FMath::Random(0.f, 180.f);
		float rotZ = FMath::Random(0.f, 180.f);
		t->SetRotation(FVector(rotX, 0, rotZ));
		t->UpdateWorld();
	}

	Renders.push_back(render);
}

void CDemo::CreateFloor()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Plane");
	render->ReadMesh(L"Plane");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X, -5.5f, Position.Z));
	t->SetScale(FVector(150, 15, 30));
	t->UpdateWorld();

	CMaterial* material = render->GetMaterial("WorldGridMaterial");
	material->SetTiling(FVector2D(6, 6));
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

	for (float x = -7.0f; x <= 7.0f; x++)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, 11.5f, Position.Z));
		t->SetScale(100.0f);
		t->UpdateWorld();
	}

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::CreateKachujin_Old()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Kachujin_Old");
	render->ReadMesh(L"Kachujin_Old/Kachujin_Old");
	render->ReadAnimation(L"Kachujin_Old/Idle");
	render->ReadAnimation(L"Kachujin_Old/Run");
	render->ReadAnimation(L"Kachujin_Old/Salsa");
	render->ReadAnimation(L"Kachujin_Old/Walk");
	render->Finish_ReadDatas();

	int index = 0;
	for (float x = -7.0f; x <= 7.0; x += 0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z + 0.5f));
		t->UpdateWorld();
		int clip = FMath::Random(0, 3);
		render->ChangeClip(index++, clip);
	}

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::CreateTurtle()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Turtle");
	render->ReadMesh(L"Turtle/Turtle");
	render->ReadAnimation(L"Turtle/Idle");
	render->ReadAnimation(L"Turtle/GuardPose");
	render->ReadAnimation(L"Turtle/Hit");
	render->ReadAnimation(L"Turtle/Attack_Scratch");
	render->Finish_ReadDatas();

	int index = 0;
	for (float x = -7.0f; x <= 7.0; x += 0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z));
		t->SetScale(0.5f);
		t->UpdateWorld();
		int clip = FMath::Random(0, 3);
		render->ChangeClip(index++, clip);

	}
	Renders.push_back(render);
}

void CDemo::DrawModelBone(CMeshRender* InMesh)
{
	CShader* shader = CShaders::Get()->GetShader(L"Sphere.fx");
	BoneDebugger = new CSphereDebugDrawer(shader, InMesh);
}
