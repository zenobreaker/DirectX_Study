#pragma once

#include "Systems/IExecutable.h"
#include "Framework.h"

class Line_Circle : public IExecutable
{
public:
	void Initialize();
	void Destroy();

	void Tick();
	void Render();

private:
	CShader* Shader;

	vector<FVertexColor> Verticies;
	ID3D11Buffer* VertexBuffer;
};