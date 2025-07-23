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

	//CreateKachujin();
	CreateKachujin_Old();
	//CreateBillboard();
	CreateSky();

	//CreateSphere();

	//CreateKachujin();
	//CreateKachujin_Old();
	CreateTurtle_Anim();

}

void CDemo::Destroy()
{

	Delete(Terrain);
	Delete(Sky);


	for(auto& render : Renders)
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


	for (auto render : Renders)
	{
		render->SetPass(pass);
		render->Tick();
	}

	if (BoneDebugger != nullptr)
		BoneDebugger->Tick();


	Sky->Tick();

	//switch (WeatherType)
	//{
	//	case EWeatherType::Rain: Rain->Tick(); break;
	//	case EWeatherType::Snow: Snow->Tick(); break;
	//}

}

void CDemo::PreRender()
{
	
}

void CDemo::Render()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	//Terrain->SetPass(Pass);
	//Terrain->Render();

	for(auto render : Renders)
		render->Render();

	if(BoneDebugger != nullptr)
		BoneDebugger->Render();

	//switch (WeatherType)
	//{
	//	case EWeatherType::Rain: Rain->Render(); break;
	//	case EWeatherType::Snow: Snow->Render(); break;
	//}
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

void CDemo::CreateSky()
{
	Sky = new CSky(L"Environments/Sky1024.dds", L"99_Environment.fx", 100.0f);
	//Rain = new CRain(FVector(300, 100, 500), 1e+4f);
	//Snow = new CSnow(FVector(300, 100, 500), 1e+4f);
}


void CDemo::CreateBillboard()
{
	Billboard = new CBillboard(L"Grass.fx");
	Billboard->AddTexture(L"Terrain/Billboard.png");
	Billboard->AddTexture(L"Terrain/Billboard2.png");
	Billboard->AddTexture(L"Terrain/Billboard3.png");

	for (UINT z = 0; z < 30; z += 3)
	{
		for (UINT x = 0; x < 30; x += 3)
		{

			FVector position = Position;
			position.X = Position.X + ((float)x + FMath::Random(0.0f, 2.5f));
			position.Y = 0.0f;
			position.Z = Position.Z + ((float)z + FMath::Random(0.0f, 2.5f));

			float randomX = FMath::Random(1.0f, 2.0f);
			float randomY = FMath::Random(3.0f, 6.0f);

			int random = FMath::Random(0, 2);
			Billboard->AddPosition(position, FVector2D(randomX, randomY), random);
		}
	}
}

void CDemo::CreateCube()
{
	Shader = CShaders::Get()->GetShader(L"Model_Lighting.fx");
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
	Shader = CShaders::Get()->GetShader(L"Model_Lighting.fx");
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Plane"); 
	render->ReadMesh(L"Plane");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X, 0.0f, Position.Z));
	t->SetScale(FVector(50, 15, 50));
	t->UpdateWorld();

	CMaterial* material = render->GetMaterial("WorldGridMaterial");
	material->SetTiling(FVector2D(6, 6));
	Renders.push_back(render);
}

void CDemo::CreateAirplane()
{
	Shader = CShaders::Get()->GetShader(L"Model_Lighting.fx");
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
	Shader = CShaders::Get()->GetShader(L"Model_Lighting.fx");
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"63/Sphere");
	render->ReadMesh(L"Sphere");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X - 1.0f, 1.0f, Position.Z));
	t->SetScale(5.0f);
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

	for (float x = -7.0f; x <= 7.0; x += 0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z + 0.5f));
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
	for (float x = -7.0f; x <= 7.0; x+=0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z+0.5f));
		t->UpdateWorld();
		int clip = FMath::Random(0, 3);
		render->ChangeClip(index++, clip);
	}

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::CreatTurtle()
{
	Shader = CShaders::Get()->GetShader(L"Model.fx");

}

void CDemo::CreateTurtle_Anim()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Turtle");
	render->ReadMesh(L"Turtle/Turtle");
	render->ReadAnimation(L"Turtle/Idle");
	//render->ReadAnimation(L"Turtle/GuardPose");
	//render->ReadAnimation(L"Turtle/Hit");
	//render->ReadAnimation(L"Turtle/Attack_Scratch");
	render->Finish_ReadDatas();

	int index = 0;
	
	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X + 2.0f, 0, Position.Z));
	t->SetScale(1.0f);
	t->UpdateWorld();
	/*int clip = FMath::Random(0, 3);
	render->ChangeClip(index++, clip);*/


	Renders.push_back(render);
}

void CDemo::DrawModelBone(CMeshRender* InMesh)
{
	CShader* shader = CShaders::Get()->GetShader(L"Sphere.fx");
	BoneDebugger = new CSphereDebugDrawer(shader, InMesh);
}
