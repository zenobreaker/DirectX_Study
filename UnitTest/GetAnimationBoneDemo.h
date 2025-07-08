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
	void CreateTurtle();

	void CreateCollision();
private:
	wstring ShaderFile;
	wstring MaterialFolder;

	FVector Position = FVector(0, 0.0f, 0);

private:
	CShader* Shader = nullptr;

	CMeshRender* Plane;
	CAnimRender* Kachujin;

	FColliderObject* Collision;
};