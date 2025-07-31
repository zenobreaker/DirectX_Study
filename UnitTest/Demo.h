#pragma once

#include "Systems/IExecutable.h"

class CDemo_MRT : public CRenderer
{
public:
	CDemo_MRT(ID3D11ShaderResourceView* InSRV);
	~CDemo_MRT();

	void Tick();
	void Render();
};

///////////////////////////////////////////////////////////////////////////////


class CDemo : public IExecutable
{
public:
	void Initialize();
	void Destroy();

	void Tick();

	void PreRender();
	void Render();
	void PostRender();


private:
	void CreateLighting();

	void CreateTerrain();


	void CreateCube();
	void CreateFloor();
	void CreateAirplane();
	void CreateSphere();
	void CreateKachujin();
	void CreateKachujin_Old();
	void CreatTurtle();
	void CreateTurtle_Anim();

	void CreateSky();
	void CreateBillboard();

	void DrawModelBone(CMeshRender* InMesh);
private:
	wstring ShaderFile;
	wstring MaterialFolder;

private:
	CRender2D* Render2D;
	CPostEffect* PostEffect;
	CDepthStencil* DepthStencil;
	CViewport* Viewport;

	CDemo_MRT* Demo_MRT;
	CRenderTarget* MRT[4];
	CRender2D* Render2D_MRT[4];

private:
	CShader* Shader;


	UINT Pass = 0;
	UINT ModelIndex = 0;

	FVector Position = FVector(120.0f, 2.0f, 90.0f);


	CSky* Sky;
	CCubeMap* CubeMap;
	CTerrain* Terrain;
	CBillboard* Billboard;

	vector<CMeshRender*> Renders;

	CSphereDebugDrawer* BoneDebugger = nullptr;

private:
	enum class EWeatherType
	{
		None = 0, Rain, Snow, Max,
	} WeatherType;

	CRain* Rain;
	CSnow* Snow;
};
