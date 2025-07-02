#include "Pch.h"
#include "GetAnimationBoneDemo.h"

void GetAnimationBoneDemo::Initialize()
{
	MaterialFolder = L"";
	CreatePlane();
	CreateKachujin();
}

void GetAnimationBoneDemo::Destroy()
{
	Delete(Plane);
	Delete(Kachujin);
}

void GetAnimationBoneDemo::Tick()
{
	Plane->Tick();
	Kachujin->Tick(); 
}

void GetAnimationBoneDemo::Render()
{
	Plane->Render(); 
	Kachujin->Tick();
}

void GetAnimationBoneDemo::CreatePlane()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	Plane = new CMeshRender(Shader);
	Plane->ReadMaterial(MaterialFolder + L"Plane");
	Plane->ReadMesh(L"Plane");

	CTransform* t = Plane->AddTransform();
	t->SetPosition(FVector(Position.X, -5.5f, Position.Z));
	t->SetScale(FVector(150, 15, 30));
	t->UpdateWorld();

	CMaterial* material = Plane->GetMaterial("WorldGridMaterial");
	material->SetTiling(FVector2D(6, 6));
}

void GetAnimationBoneDemo::CreateKachujin()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	Kachujin = new CAnimRender(Shader);
	Kachujin->ReadMaterial(MaterialFolder + L"Kachujin");
	Kachujin->ReadMesh(L"Kachujin/Kachujin");
	Kachujin->ReadAnimation(L"Kachujin/Idle");
	Kachujin->Finish_ReadDatas();

	
	CTransform* t = Kachujin->AddTransform();
	t->SetPosition(FVector(-5.0f, .0f, 0.0f));
	t->SetScale(100.f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(-2.5f, .0f, 0.0f));
	t->SetScale(0.01f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(0.0f, .0f, 0.0f));
	t->SetScale(0.01f);
	t->UpdateWorld();


	t = Kachujin->AddTransform();
	t->SetPosition(FVector(+2.5f, .0f, 0.0f));
	t->SetScale(0.01f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(+5.0f, .0f, 0.0f));
	t->SetScale(0.01f);
	t->UpdateWorld();
	
	Kachujin->ChangeClip(0, 0);
}
