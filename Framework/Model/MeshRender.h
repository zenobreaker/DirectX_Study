#pragma once

class CMeshRender
{
public:
	CMeshRender(CShader* InShader);
	virtual ~CMeshRender();

	virtual void Tick();
	virtual void Render();

public:
	CTransform* AddTransform();
	CTransform* GetTransform(UINT InIndex);

public:
	CMaterial* GetMaterial(const string& InName);

	void SetInstanceColor(UINT InIndex, const FColor& InColor);
	
	void AddInstanceTexture(wstring InFile);
	void SetInstanceTexture(UINT InIndex, UINT InTexture);

public:
	void ReadMaterial(wstring InName);
	void ReadMesh(wstring InName);

public:
	UINT GetMeshCount() { return Meshes.size(); }
	vector<CModelMesh*>& GetMeshes() { return Meshes; }
	CModelMesh* GetMeshByIndex(UINT InIndex) { return Meshes[InIndex]; }
	CModelMesh* GetMeshByName(string InName);

private:
	void ReadMaterialData(const Json::Value& InValue);
	void ReadBoneData(CBinaryReader* InReader);
	void ReadMeshData(CBinaryReader* InReader);

private:
	map<string, CMaterial*> MaterialTable;

protected:
	CShader* Shader;

	vector<CModelBone*> Bones;
	vector<CModelMesh*> Meshes;

private:
	CFrame* Frame;

private:
	struct FDesc
	{
		FMatrix BoneTransforms[MAX_MODEL_TRANSFORMS];
		FMatrix OffsetTransforms[MAX_MODEL_TRANSFORMS];
	} Data;
	CConstantBuffer* CBuffer;

private:
	vector<CTransform*> Transforms;
	FMatrix Worlds[MAX_INSTANCE_COUNT];

	CVertexBuffer* InstanceBuffer;

private:
	struct FInstanceColorDesc
	{
		FColor Color = FColor::White;

		int Texture = -1;
		float Padding[3];
	};
	FInstanceColorDesc InstanceColorDatas[MAX_INSTANCE_COUNT];

	CConstantBuffer* CInstanceColorBuffer;

	vector<wstring> InstanceTextureFiles;
	CTextureArray* InstanceTextures = nullptr;
};