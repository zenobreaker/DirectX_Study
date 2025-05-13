#include "Framework.h"
#include "Renderer.h"

CRenderer::CRenderer(wstring InFile)
	: File(InFile)
{
	Shader = CShaders::Get()->GetShader(InFile);

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
