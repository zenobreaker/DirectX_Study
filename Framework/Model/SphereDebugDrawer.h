#pragma once

class CSphereDebugDrawer
{
public:
	CSphereDebugDrawer(CShader* InShader, CMeshRender* InTargetMesh);
	virtual ~CSphereDebugDrawer();

	virtual void Tick();
	virtual void Render();

private:
	CShader* Shader; 
	UINT ModelIndex = 0;

	vector<FVector> BonePoints;
	CMeshRender* TargetMesh; 
	CMeshRender* Sphere;
};