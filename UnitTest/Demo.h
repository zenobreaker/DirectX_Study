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
	CShader* Shader; 
	
	UINT Address = 0; 

	UINT VertexCount = 4; 
	FVertexTexture* Vertices; 
	ID3D11Buffer* VertexBuffer;

	UINT IndexCount= 6; 
	UINT* Indices; 
	ID3D11Buffer* IndexBuffer;

	FMatrix World; 
	FMatrix View; 
	FMatrix Projection; 

	ISRV* SRV = nullptr;
};