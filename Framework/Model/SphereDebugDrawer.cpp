#include "Framework.h"
#include "SphereDebugDrawer.h"
#include <iostream>

CSphereDebugDrawer::CSphereDebugDrawer(CShader* InShader, CMeshRender* InTargetMesh)
	: Shader(InShader), TargetMesh(InTargetMesh)
{
	Sphere = new CMeshRender(Shader);
	Sphere->ReadMaterial(L"Sphere");
	Sphere->ReadMesh(L"Sphere");

	FMatrix world = TargetMesh->GetTransform(0)->GetMatrix();
	for (UINT i = 0; i < TargetMesh->GetBoneCount(); i++)
	{
		CTransform* t = Sphere->AddTransform();
		t->SetScale(FVector(1.0f));
		t->UpdateWorld();

		FMatrix matrix = TargetMesh->UpdateBoneTransformWithIndex(i);
		BonePoints.push_back(FVector::TransformCoord(FVector::Zero, matrix * world));
	}
}

CSphereDebugDrawer::~CSphereDebugDrawer()
{
	Delete(Sphere);
}

void CSphereDebugDrawer::Tick()
{
	CheckNull(Sphere);

	FMatrix world = TargetMesh->GetTransform(0)->GetMatrix();
	for (UINT i = 0; i < TargetMesh->GetBoneCount(); i++)
	{
		FMatrix matrix = TargetMesh->UpdateBoneTransformWithIndex(i);

		CTransform* t = Sphere->GetTransform(i);
		t->SetPosition(FVector::TransformCoord(FVector::Zero, matrix * world));
		t->UpdateWorld();
	}

}

void CSphereDebugDrawer::Render()
{
	CheckNull(Sphere);


	Sphere->Tick();
	Sphere->Render();
}
