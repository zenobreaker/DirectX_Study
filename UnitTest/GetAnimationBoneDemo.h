#pragma once

#include "Systems/IExecutable.h"

class GetAnimationBoneDemo: public IExecutable
{
public:
	void Initialize();
	void Destroy(); 
	void Tick(); 
	void Render(); 

private:
	void CreatePlane(); 
	void CreateKachujin();

private:
	wstring ShaderFile;
	wstring MaterialFolder;

	FVector Position = FVector(0, 0.0f, 90.0f);

private:
	CShader* Shader = nullptr;

	CMeshRender* Plane;
	CAnimRender* Kachujin;
};