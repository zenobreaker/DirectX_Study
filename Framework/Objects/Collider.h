#pragma once

struct FColliderObject
{
	class CTransform* Origin = nullptr;
	class CTransform* Relative = nullptr;

	class CCollider* Collider = nullptr;

	~FColliderObject();

	void Tick();
	void Render();
};


class CCollider
{
public:
	CCollider(CTransform* InRelative, CTransform* InOrigin);
	~CCollider(); 

	void Tick();
	void Render(FColor InColor = FColor(0, 1, 1,1));

	CTransform* GetRelative() { return Relative; }

private:
	CTransform* Origin = nullptr;
	CTransform* Relative = nullptr;

	FVector Points[8];
};