#include "Pch.h"
#include "TextureBufferDemo.h"

void CTextureBufferDemo::Initialize()
{
	Case1();
	Case2();
	Case3();
}

void CTextureBufferDemo::Destroy()
{
	Delete(Render2D);
	Delete(Image);
}

void CTextureBufferDemo::Tick()
{
	Render2D->Tick();
}

void CTextureBufferDemo::Render()
{
	Render2D->Render();
}

void CTextureBufferDemo::Case1()
{
	Image = new CTexture(L"Environments/Background.png");
	TBuffer = new CTextureBuffer(Image->GetTexture());

	CShader* shader = new CShader(L"TextureBuffer.fx");
	shader->AsSRV("Input")->SetResource(*TBuffer);
	shader->AsUAV("Output")->SetUnorderedAccessView(*TBuffer);

	UINT width = TBuffer->GetWidth();
	UINT height = TBuffer->GetHeight();

	float x = ((float)width / 32) < 1.0f ? 1.0f : ((float)width / 32);
	float y = ((float)height / 32) < 1.0f ? 1.0f : ((float)height / 32);

	shader->Dispatch(0, 0, (UINT)ceil(x), (UINT)ceil(y), 1);

	Render2D = new CRender2D(TBuffer->GetOutputSRV());

	FVector scale(CD3D::GetDesc().Width, CD3D::GetDesc().Height, 1);
	Render2D->GetTransform()->SetScale(scale);

	FVector position(CD3D::GetDesc().Width * 0.5f, CD3D::GetDesc().Height * 0.5f, 0);
	Render2D->GetTransform()->SetPosition(position);
}

void CTextureBufferDemo::Case2()
{
	Image = new CTexture(L"Environments/Background.png");
	TBuffer = new CTextureBuffer(Image->GetTexture());

	CShader* shader = new CShader(L"TextureBuffer.fx");
	shader->AsSRV("Input")->SetResource(*TBuffer);
	shader->AsUAV("Output")->SetUnorderedAccessView(*TBuffer);

	UINT width = TBuffer->GetWidth();
	UINT height = TBuffer->GetHeight();

	float x = ((float)width / 32) < 1.0f ? 1.0f : ((float)width / 32);
	float y = ((float)height / 32) < 1.0f ? 1.0f : ((float)height / 32);

	shader->Dispatch(0, 1, (UINT)ceil(x), (UINT)ceil(y), 1);

	Render2D = new CRender2D(TBuffer->GetOutputSRV());

	FVector scale(CD3D::GetDesc().Width, CD3D::GetDesc().Height, 1);
	Render2D->GetTransform()->SetScale(scale);

	FVector position(CD3D::GetDesc().Width * 0.5f, CD3D::GetDesc().Height * 0.5f, 0);
	Render2D->GetTransform()->SetPosition(position);
}

void CTextureBufferDemo::Case3()
{
	Image = new CTexture(L"Environments/Compute1.png");
	Image2 = new CTexture(L"Environments/Compute2.png");
	TBuffer = new CTextureBuffer(Image->GetTexture());
	TBuffer2 = new CTextureBuffer(Image2->GetTexture());

	CShader* shader = new CShader(L"TextureBuffer.fx");
	shader->AsSRV("Input")->SetResource(*TBuffer);
	shader->AsSRV("Input2")->SetResource(*TBuffer2);
	shader->AsUAV("Output")->SetUnorderedAccessView(*TBuffer);

	UINT width = TBuffer->GetWidth();
	UINT height = TBuffer->GetHeight();

	float x = ((float)width / 32) < 1.0f ? 1.0f : ((float)width / 32);
	float y = ((float)height / 32) < 1.0f ? 1.0f : ((float)height / 32);

	shader->Dispatch(0, 2, (UINT)ceil(x), (UINT)ceil(y), 1);

	Render2D = new CRender2D(TBuffer->GetOutputSRV());

	FVector scale(CD3D::GetDesc().Width, CD3D::GetDesc().Height, 1);
	Render2D->GetTransform()->SetScale(scale);

	FVector position(CD3D::GetDesc().Width * 0.5f, CD3D::GetDesc().Height * 0.5f, 0);
	Render2D->GetTransform()->SetPosition(position);
}
