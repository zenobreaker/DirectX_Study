#pragma once

#include "Systems/IExecutable.h"

class CRectangle : public IExecutable
{
private:
	static const int VertexCount; 

public:
	void Initialize();
	void Destroy();

	void Tick();
	void Render();

private:
	CShader* Shader;

	FVertex* Verticies;
	ID3D11Buffer* VertexBuffer;
};