#pragma once

struct FPointLight
{
	FColor Diffuse;
	FColor Specular;
	FColor Emissive;

	FVector Position;
	float Range;

	float Intensity;
	float Padding[3];
};

struct FSpotLight : public FPointLight
{
	FVector Direction;
	float Angle;
};

///////////////////////////////////////////////////////////////////////////////

struct FPointLightDesc
{
	UINT Count = 0;
	FVector Padding;

	FPointLight Lights[MAX_LIGHT_COUNT];
};

struct FSpotLightDesc
{
	UINT Count = 0;
	FVector Padding;

	FSpotLight Lights[MAX_LIGHT_COUNT];
};

///////////////////////////////////////////////////////////////////////////////

class CLighting
{
public:
	static void Create();
	static void Destroy();

	static CLighting* Get();

private:
	CLighting();
	~CLighting();

public:
	void Tick();

public:
	FPointLightDesc* GetPointLightData() { return &PointLightData; }
	FSpotLightDesc* GetSpotLightData() { return &SpotLightData; }

private:
	static CLighting* Instance;

public:
	void AddPointLight(const FPointLight& InLight);
	void AddSpotLight(const FSpotLight& InLight);

private:
	bool bShowGUI = false;

private:
	FPointLightDesc PointLightData;
	FSpotLightDesc SpotLightData;
};