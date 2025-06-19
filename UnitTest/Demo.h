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
	void CreateAirplane(); 
	void CreateSphere(); 
	void CreateKachujin(); 
	void CreateKachujin_Old(); 

	void DrawModelBone(CMeshRender* InMesh);
private:
	wstring ShaderFile;
	wstring MaterialFolder;

private:
	CShader* Shader;

	UINT Pass = 0; 
	CTerrain* Terrain;

	vector<CMeshRender*> Renders; 

	CSphereDebugDrawer* BoneDebugger = nullptr;
};
