#pragma once

#include "Systems/IExecutable.h"
#include "Framework.h"

class Line : public IExecutable
{
public:
	void Initialize();
	void Destroy();

	void Tick();
	void Render();

private:
	CShader* shader;

	FVector Verticies[2];
	ID3D11Buffer* VertexBuffer;
};