#pragma once

#include "Systems/IExecutable.h"

class CDemo : public IExecutable
{
private:
	static const int VertexCount; 
	static const int IndexCount;
public:
	void Initialize();
	void Destroy();

	void Tick();

	void PreRender();
	void Render();
	void PostRender();


private:
	CShader* Shader; 
	
	FVertex* Vertices; 
	ID3D11Buffer* VertexBuffer;

	UINT* Indices; 
	ID3D11Buffer* IndexBuffer;

	FMatrix World; 
	FMatrix View; 
	FMatrix Projection; 
};