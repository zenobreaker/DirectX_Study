#include "Framework.h"
#include "MeshRender.h"
#include <fstream>

CMeshRender::CMeshRender(CShader* InShader)
	: Shader(InShader)
{
	Frame = new CFrame(Shader);

	CBuffer = new CConstantBuffer(Shader, "CB_BoneTransforms", &Data, sizeof(FDesc));
	InstanceBuffer = new CVertexBuffer(Worlds, MAX_INSTANCE_COUNT, sizeof(FMatrix), INSTANCE_SLOT_NUMBER, true);
	
	CInstanceColorBuffer = new CConstantBuffer(Shader, "CB_InstanceColors", InstanceColorDatas, sizeof(FInstanceColorDesc) * MAX_INSTANCE_COUNT);
}

CMeshRender::~CMeshRender()
{
	for (CModelMesh* mesh : Meshes)
		Delete(mesh);

	Delete(Frame);

	Delete(CBuffer);
	Delete(InstanceBuffer);
	Delete(CInstanceColorBuffer);

	Delete(InstanceTextures);
}

void CMeshRender::Tick()
{
	if (InstanceTextures == nullptr && InstanceTextureFiles.size() > 0)
		InstanceTextures = new CTextureArray(Shader, "InstanceMaps", InstanceTextureFiles, false);

	for (CModelMesh* mesh : Meshes)
		mesh->Tick();
}

void CMeshRender::Render()
{
	IA_TRIANGLELIST();

	Frame->Render();
	CBuffer->Render();

	InstanceBuffer->Mapping();
	InstanceBuffer->Render();

	CInstanceColorBuffer->Render();
	
	if (InstanceTextures != nullptr)
		InstanceTextures->Render();

	for (CModelMesh* mesh : Meshes)
		mesh->Render();
}

CTransform* CMeshRender::AddTransform()
{
	int index = Transforms.size();
	
	CTransform* transform = new CTransform(&Worlds[index]);
	Transforms.push_back(transform);

	return transform;
}

CTransform* CMeshRender::GetTransform(UINT InIndex)
{
	Assert(InIndex < Transforms.size(), "잘못된 Transforms 번호");

	return Transforms[InIndex];
}

CMaterial* CMeshRender::GetMaterial(const string& InName)
{
	map<string, CMaterial*>::iterator iter = MaterialTable.find(InName);

	if (iter == MaterialTable.end())
		return nullptr;

	return iter->second;
}

void CMeshRender::SetInstanceColor(UINT InIndex, const FColor& InColor)
{
	InstanceColorDatas[InIndex].Color = InColor;
}

void CMeshRender::AddInstanceTexture(wstring InFile)
{
	InstanceTextureFiles.push_back(InFile);
}

void CMeshRender::SetInstanceTexture(UINT InIndex, UINT InTexture)
{
	InstanceColorDatas[InIndex].Texture = InTexture;
}

void CMeshRender::ReadMaterial(wstring InName)
{
	InName = L"../../_Materials/" + InName + L".material";

	ifstream stream;
	stream.open(InName);

	Json::Value root;
	stream >> root;
	stream.close();

	ReadMaterialData(root);
}

void CMeshRender::ReadMaterialData(const Json::Value& InValue)
{
	Json::Value::Members members = InValue.getMemberNames();
	for (string name : members)
	{
		CMaterial* material = new CMaterial(Shader);
		Json::Value value = InValue[name];

		material->SetDraw(value["00_Draw"].asBool());
		material->SetTechnique(value["01_Technique"].asUInt());
		material->SetPass(value["02_Pass"].asUInt());

		material->SetAmbient(CString::FromColor(value["03_Ambient"].asString()));
		material->SetDiffuse(CString::FromColor(value["04_Diffuse"].asString()));
		material->SetSpecular(CString::FromColor(value["05_Specular"].asString()));
		material->SetEmissive(CString::FromColor(value["06_Emissive"].asString()));

		if (value["07_DiffuseMap"].asString().size() > 0)
			material->SetDiffuseMap(CString::ToWString(value["07_DiffuseMap"].asString()), false);

		if (value["08_SpecularMap"].asString().size() > 0)
			material->SetSpecularMap(CString::ToWString(value["08_SpecularMap"].asString()), false);

		if (value["09_NormalMap"].asString().size() > 0)
			material->SetNormalMap(CString::ToWString(value["09_NormalMap"].asString()), false);

		MaterialTable[name] = material;
	}		
}

void CMeshRender::ReadMesh(wstring InName)
{
	InName = L"../../_Models/" + InName + L".mesh";

	CBinaryReader* reader = new CBinaryReader();
	reader->Open(InName);

	ReadBoneData(reader);
	ReadMeshData(reader);

	reader->Close();
	Delete(reader);


	for (UINT i = 0; i < Bones.size(); i++)
	{
		CModelBone* bone = Bones[i];

		Data.BoneTransforms[i] = Bones[i]->Transform;
		Data.OffsetTransforms[i] = Bones[i]->OffsetTransform;

		if (bone->ParentIndex < 0)
			continue;

		bone->Parent = Bones[bone->ParentIndex];
		bone->Parent->Children.push_back(bone);
	}

	for (CModelMesh* mesh : Meshes)
	{
		mesh->CreateBuffer(Shader);
		mesh->Material = MaterialTable[mesh->MaterialName];
	}
}

void CMeshRender::ReadBoneData(CBinaryReader* InReader)
{
	UINT count = InReader->FromUInt();
	for (UINT i = 0; i < count; i++)
	{
		CModelBone* bone = new CModelBone();

		bone->Index = InReader->FromUInt();
		bone->Name = InReader->FromString();

		bone->ParentIndex = InReader->FromInt();
		bone->Transform = InReader->FromMatrix();
		bone->OffsetTransform = InReader->FromMatrix();

		Bones.push_back(bone);
	}
}

void CMeshRender::ReadMeshData(CBinaryReader* InReader)
{
	UINT count = InReader->FromUInt();
	for (UINT i = 0; i < count; i++)
	{
		CModelMesh* mesh = new CModelMesh();

		mesh->Name = InReader->FromString();
		mesh->MaterialName = InReader->FromString();
		mesh->Data.BoneIndex = InReader->FromUInt();

		mesh->VertexCount = InReader->FromUInt();
		mesh->Vertices = new FVertexModel[mesh->VertexCount];
		InReader->FromByte((void**)&mesh->Vertices, sizeof(FVertexModel) * mesh->VertexCount);

		mesh->IndexCount = InReader->FromUInt();
		mesh->Indices = new UINT[mesh->IndexCount];
		InReader->FromByte((void**)&mesh->Indices, sizeof(UINT) * mesh->IndexCount);

		Meshes.push_back(mesh);
	}
}

CModelMesh* CMeshRender::GetMeshByName(string InName)
{
	for (CModelMesh* mesh : Meshes)
	{
		if (mesh->Name == InName)
			return mesh;
	}

	return nullptr;
}