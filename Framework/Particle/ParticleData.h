#pragma once
#include "Framework.h"

struct FParticleData
{
public:
	enum class EBlendType
	{
		Opaque = 0, Additive, AlphaBlend, Multiply, Multiply2X,
	} Type = EBlendType::Opaque;

public:
	bool bLoop = false;

	wstring TextureFile;

public:
	UINT MaxParticle = 100;

public:
	float ReadyTime = 1.0f;
	float ReadyRandomTime = 0.0f;

public:
	float StartVelocity = 1;
	float EndVelocity = 1;

	float MinHorizontalVelocity = 0;
	float MaxHorizontalVelocity = 0;

	float MinVerticalVelocity = 0;
	float MaxVerticalVelocity = 0;

public:
	float MinRotateSpeed = 0;
	float MaxRotateSpeed = 0;

public:
	float MinStartSize = 100;
	float MaxStartSize = 100;

	float MinEndSize = 100;
	float MaxEndSize = 100;

public:
	FVector Gravity = FVector::Zero;

public:
	float ColorAmount = 1.0f;
	FColor MinColor = FColor(1, 1, 1, 1);
	FColor MaxColor = FColor(1, 1, 1, 1);
};
