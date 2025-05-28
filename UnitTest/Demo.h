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

private:
	wstring ShaderFile;

private:
	UINT Pass = 0; 
	CTerrain* Terrain;
};
