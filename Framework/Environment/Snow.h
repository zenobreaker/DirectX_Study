#pragma once

class CSnow : public CRenderer
{
public:
	CSnow(const FVector& InExtent, UINT InDrawCount);
	~CSnow();

	void Tick();
	void Render();

private:
	struct FVertexSnow
	{
		FVector Position;
		FVector2D Scale;
		FVector2D Random;
	};

private:
	struct FDesc
	{
		FColor Color = FColor(1, 1, 1, 1);

		FVector Velocity = FVector(0.0f, -2.0f, 0.0f);
		float DrawDistance = 0;

		FVector Origin = FVector::Zero;
		float Turbulence = 2.0f;

		FVector Extent = FVector::Zero;
		float Padding;
	} Data;
	CConstantBuffer* CBuffer;

private:
	UINT DrawCount;

	CTexture* Texture;
};