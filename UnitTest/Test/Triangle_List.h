#pragma once

#include "Systems/IExecutable.h"
#include "Framework.h"

class Triangle_List : public IExecutable
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
	ID3D11Buffer* VertexBuffer2;
};