#pragma once

class CRenderer
{
public:
	CRenderer(wstring InFile);
	CRenderer(CShader* InShader);
	virtual ~CRenderer();

	void SetPass(UINT InPass);

	virtual void Tick();
	virtual void Render();

	CTransform* GetTransform() { return Transform; }

private:
	void Initialize();

protected:
	wstring File = L"";
	CShader* Shader;

	CTransform* Transform;
	CFrame* Frame;

	CVertexBuffer* VBuffer = nullptr;
	CIndexBuffer* IBuffer = nullptr;

	UINT VCount = 0;
	UINT ICount = 0;
};