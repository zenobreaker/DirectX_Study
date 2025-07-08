#pragma once
#define MAX_RENDER_LINE 15000

class CRenderLine
{
public:
	static void Create();
	static void Destroy();

	static CRenderLine* Get();

private:
	static CRenderLine* Instance;

private:
	CRenderLine();
	~CRenderLine();

public:
	void Tick();
	void Render();

public:
	void Draw(const FVector& InStart, const FVector& InEnd);
	void Draw(const FVector& InStart, const FVector& InEnd, const FColor& InColor);


private:
	CShader* Shader; 

	CTransform* World; 
	CFrame* PerFrame;

	CVertexBuffer* VBuffer; 
	FVertexColor* Vertices;

	UINT Count = 0;
};