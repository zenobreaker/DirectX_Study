#pragma once

class CContext
{
public:
	static void Create();
	static void Destroy();

	static CContext* Get();

private:
	CContext();
	~CContext();

public:
	void Tick();
	void Tick_View();
	void Tick_WorldTime();
	void Tick_Light();

	void Render();

	void ResizeScreen();

public:
	class CCamera* GetCamera() { return View; }

public:
	FMatrix GetViewMatrix();
	FMatrix GetProjectionMatrix();

public:
	FVector GetLightDirection() { return LightDirection; }
	float GetLightIntensity() { return LightIntensity; }

	float GetSunAngle() { return SunAngle; }

	FColor GetAmbientColor() { return Ambient; }
	FColor GetSpecularColor() { return Specular; }

public:
	void SetHideSetting(bool InValue) { bHideSetting = InValue; }

private:
	static CContext* Instance;

private:
	bool bHideSetting = false;

	CCamera* View;
	FMatrix Projection;
	D3D11_VIEWPORT* Viewport;

	float LightAngle;
	float LightIntensity;
	FVector LightDirection = FVector(-1, -1, +1);

	float SunAngle;

	FColor Ambient = FColor(0, 0, 0, 1);
	FColor Specular = FColor(1, 1, 1, 1);
};