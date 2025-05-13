#include "Framework.h"
#include "ModelMesh.h"

CModelMesh::CModelMesh()
{
	
}

CModelMesh::~CModelMesh()
{
	DeleteArray(Vertices);
	DeleteArray(Indices);

	Delete(VertexBuffer);
	Delete(IndexBuffer);

	Delete(CBuffer);
}

void CModelMesh::CreateBuffer(CShader* InShader)
{
	Shader = InShader;

	VertexBuffer = new CVertexBuffer(Vertices, VertexCount, sizeof(FVertexModel));
	IndexBuffer = new CIndexBuffer(Indices, IndexCount);
	
	CBuffer = new CConstantBuffer(Shader, "CB_BoneIndex", &Data, sizeof(FDesc));
}

void CModelMesh::Tick()
{
	
}

void CModelMesh::Render()
{
	CheckFalse(Material->GetDraw());

	VertexBuffer->Render();
	IndexBuffer->Render();

	Material->Render();
	CBuffer->Render();

	IA_TRIANGLELIST();
	Shader->DrawIndexedInstanced(IndexCount, MAX_INSTANCE_COUNT);
}