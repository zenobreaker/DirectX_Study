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


private:
	wstring ShaderFile;
	wstring MaterialFolder;

private:
	CShader* Shader;

	UINT Pass = 0; 
	CTerrain* Terrain;

	CMeshRender* Cube = nullptr;
};
