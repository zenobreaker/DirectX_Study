#pragma once

class CRain : public CRenderer
{
public:
	CRain(const FVector& InExtent, UINT InDrawCount);
	~CRain();

	void Tick();
	void Render();

private:
	struct FVertexRain
	{
		FVector Position;
		FVector2D Scale;
	};

private:
	struct FDesc
	{
		FColor Color = FColor(1, 1, 1, 1);

		FVector Velocity = FVector(-10, -100, +10);
		float DrawDistance = 0;

		FVector Origin = FVector::Zero;
		float Turbulence = 0.0f;

		FVector Extent = FVector::Zero;
		float Padding;
	} Data;
	CConstantBuffer* CBuffer;

private:
	UINT DrawCount;
	
	CTexture* Texture;
};