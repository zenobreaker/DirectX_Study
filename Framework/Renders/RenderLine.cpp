#include "Framework.h"
#include "RenderLine.h"


CRenderLine* CRenderLine::Instance = nullptr;

void CRenderLine::Create()
{
	assert(Instance == nullptr);

	Instance = new CRenderLine();
}

void CRenderLine::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CRenderLine* CRenderLine::Get()
{
	return Instance;
}

CRenderLine::CRenderLine()
{
	Shader = new CShader(L"00_RenderLine.fx");

	World = new CTransform(Shader);
	PerFrame = new CFrame(Shader);

	Vertices = new FVertexColor[MAX_RENDER_LINE];
	ZeroMemory(Vertices, sizeof(FVertexColor) * MAX_RENDER_LINE);

	// CPU에서 지속적으로 변경함을 GPU에게 전달하도록 플래그 수정
	VBuffer = new CVertexBuffer(Vertices, MAX_RENDER_LINE, sizeof(FVertexColor), 0, true);
}

CRenderLine::~CRenderLine()
{
	DeleteArray(Vertices);
	Delete(VBuffer);
	Delete(PerFrame);
	Delete(World);
	Delete(Shader); 
}

void CRenderLine::Tick()
{
}

void CRenderLine::Render()
{
	CheckFalse(Count > 0); 

	World->Render(); 
	VBuffer->Mapping();	// CPU가 GPU 메모리에 데이터를 쓰도록
	VBuffer->Render();	// 버퍼 바인딩
	PerFrame->Render();

	IA_LINELIST();
	Shader->Draw(Count);
	
	Count = 0;
	ZeroMemory(Vertices, sizeof(FVertexColor) * MAX_RENDER_LINE);
}

// 아래 함수가 호출되면 변경을 반영해야 하므로 버퍼는 CPU write를 켜야한다.
void CRenderLine::Draw(const FVector& InStart, const FVector& InEnd)
{
	Draw(InStart, InEnd, FColor(0, 1, 0, 1));
}

void CRenderLine::Draw(const FVector& InStart, const FVector& InEnd, const FColor& InColor)
{
	Vertices[Count].FColor = InColor;
	Vertices[Count++].Position = InStart;

	Vertices[Count].FColor = InColor;
	Vertices[Count++].Position = InEnd;
}
