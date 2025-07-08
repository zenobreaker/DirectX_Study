#include "Pch.h"
#include "GetAnimationBoneDemo.h"

void GetAnimationBoneDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(21, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(0, 5.5f, -20));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);


	MaterialFolder = L"";
	CreatePlane();
	CreateKachujin();

	CreateCollision();
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

	Collision->Tick();
}

void GetAnimationBoneDemo::Render()
{
	float x = sinf(CTimer::Get()->GetRunningTime() ) * 5.0f;

	CRenderLine::Get()->Draw(FVector(x, 0, 0), FVector(x, 10., 0));

	Plane->Render(); 
	Kachujin->Render();

	Collision->Render();
}

void GetAnimationBoneDemo::CreatePlane()
{
	Shader = CShaders::Get()->GetShader(L"Cube.fx");
	Plane = new CMeshRender(Shader);
	Plane->ReadMaterial(MaterialFolder + L"Plane");
	Plane->ReadMesh(L"Plane");

	CTransform* t = Plane->AddTransform();
	t->SetPosition(FVector(Position.X, Position.Y, Position.Z));
	t->SetScale(FVector(150, 15, 150));
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
	t->SetPosition(FVector(Position.X - 5.0f, Position.Y, Position.Z));
	t->SetScale(10.0f);
	t->UpdateWorld();
	
	t = Kachujin->AddTransform();
	t->SetPosition(FVector(Position.X - 2.5f, Position.Y, Position.Z));
	t->SetScale(10.0f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(Position.X, Position.Y, Position.Z));
	t->SetScale(10.0f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(Position.X + 2.5f, Position.Y, Position.Z));
	t->SetScale(10.0f);
	t->UpdateWorld();

	t = Kachujin->AddTransform();
	t->SetPosition(FVector(Position.X + 5.0f, Position.Y, Position.Z));
	t->SetScale(10.0f);
	t->UpdateWorld();
}

void GetAnimationBoneDemo::CreateTurtle()
{

}

void GetAnimationBoneDemo::CreateCollision()
{

	Collision = new FColliderObject();
	Collision->Origin = new CTransform();
	Collision->Origin->SetPosition(FVector::Zero);
	Collision->Origin->SetScale(FVector::One);

	Collision->Relative = new CTransform();
	Collision->Collider = new CCollider(Collision->Relative, Collision->Origin);
}
