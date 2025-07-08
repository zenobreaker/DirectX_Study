#include "Framework.h"
#include "Collider.h"

 FColliderObject::~FColliderObject()
{
	Delete(Origin);
	Delete(Relative);
	Delete(Collider);
}

 void FColliderObject::Tick()
{
	CheckNull(Collider);

	Collider->Tick();
}

 void FColliderObject::Render()
{
	CheckNull(Collider);

	Collider->Render();
}

//-----------------------------------------------------------------------------

CCollider::CCollider(CTransform* InRelative, CTransform* InOrigin)
	: Relative(InRelative), Origin(InOrigin)
{
	Points[0] = FVector(-0.5f, -0.5f, -0.5f);
	Points[1] = FVector(-0.5f, +0.5f, -0.5f);
	Points[2] = FVector(+0.5f, -0.5f, -0.5f);
	Points[3] = FVector(+0.5f, +0.5f, -0.5f);

	Points[4] = FVector(-0.5f, -0.5f, +0.5f);
	Points[5] = FVector(-0.5f, +0.5f, +0.5f);
	Points[6] = FVector(+0.5f, -0.5f, +0.5f);
	Points[7] = FVector(+0.5f, -0.5f, +0.5f);
}

CCollider::~CCollider()
{

}

void CCollider::Tick()
{
}

void CCollider::Render(FColor InColor)
{
	CTransform t;
	t.SetMatrix(Relative->GetMatrix());

	if (Origin != nullptr)
		t.SetMatrix(Origin->GetMatrix() * Relative->GetMatrix());

	FMatrix world = t.GetMatrix();

	FVector dests[8];

	for (UINT i = 0; i < 8; i++)
		dests[i] = FVector::TransformCoord(Points[i], world);

	// Front 
	CRenderLine::Get()->Draw(dests[0], dests[1], InColor);
	CRenderLine::Get()->Draw(dests[1], dests[3], InColor);
	CRenderLine::Get()->Draw(dests[3], dests[2], InColor);
	CRenderLine::Get()->Draw(dests[0], dests[0], InColor);

	// Backward
}
