#pragma once

#include "Systems/IExecutable.h"

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
	void CreateTerrain();
	

	void CreateCube(); 
	void CreateFloor(); 
	void CreateAirplane(); 
	void CreateSphere(); 
	void CreateKachujin(); 
	void CreateKachujin_Old(); 
	void CreateTurtle();

	void CreateSky();
	void CreateCubeMap();
	void CreateBillboard();


	void DrawModelBone(CMeshRender* InMesh);
private:
	wstring ShaderFile;
	wstring MaterialFolder;

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
