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
	UINT Width = 4;
	UINT Height = 4; 

	CShader* Shader; 
	
	UINT VertexCount; 
	FVertex* Vertices; 
	ID3D11Buffer* VertexBuffer;

	UINT IndexCount; 
	UINT* Indices; 
	ID3D11Buffer* IndexBuffer;

	FMatrix World; 
	FMatrix View; 
	FMatrix Projection; 
};