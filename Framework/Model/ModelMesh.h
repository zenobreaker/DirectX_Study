#pragma once

class CModelMesh
{
public:
	friend class CMeshRender;

private:
	CModelMesh();
	~CModelMesh();

	void CreateBuffer(CShader* InShader);

	void Tick();
	void Render();

private:
	CShader* Shader;

	string Name;
	
	string MaterialName;
	CMaterial* Material;

	CVertexBuffer* VertexBuffer;
	UINT VertexCount;
	FVertexModel* Vertices;

	CIndexBuffer* IndexBuffer;
	UINT IndexCount;
	UINT* Indices;

private:
	struct FDesc
	{
		UINT BoneIndex = 0;

		float Padding[3];
	} Data;
	CConstantBuffer* CBuffer;
};