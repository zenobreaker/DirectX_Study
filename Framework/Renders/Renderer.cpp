#include "Framework.h"
#include "Renderer.h"

CRenderer::CRenderer(wstring InFile)
	: File(InFile)
{
	Shader = new CShader(InFile);

	Initialize();
}

CRenderer::CRenderer(CShader* shader)
	: Shader(shader)
{
	Initialize();
}

void CRenderer::Initialize()
{
	assert(Shader != nullptr);

	Frame = new CFrame(Shader);
	Transform = new CTransform(Shader);
}

CRenderer::~CRenderer()
{
	Delete(Frame);
	Delete(Transform);

	Delete(VBuffer);
	Delete(IBuffer);
}

void CRenderer::SetPass(UINT InPass)
{
	Shader->SetPassNumber(InPass);
}

void CRenderer::Tick()
{

}

void CRenderer::Render()
{
	if (VBuffer != nullptr)
	{
		VBuffer->Render();

		if (IBuffer != nullptr)
			IBuffer->Render();
	}

	Frame->Render();
	Transform->Render();
}
