#pragma once


class CConverter
{
public:
	CConverter(); 
	~CConverter(); 

	void ReadFile(wstring InFileName, float InGlobalScale = 1.0f); 

public:
	void ExportMesh(wstring InSaveFileName);

private:
	void ReadMeshData();
	
	void ReadBoneData(aiNode* InNode, UINT InIndex, int InParent);
	void ReadMeshData(aiNode* InNode, UINT InBoneIndex);
	void ReadSkinData();

	void WriteMeshData(wstring InSaveFileName); 

public:
	void ExportMaterial(wstring InSaveFileName);

private:
	void ReadMaterials(); 
	void WriteMaterial(wstring InSaveFileName); 
	
	string SaveTexture(string InSaveFolder, string InFileName);

public:
	void ExportAnimation(wstring InSaveFileName, int InClipIndex = 0);

private:
	struct FClipData* ReadClipData(aiAnimation* InAnimation);
	void WriteClipData(wstring InSaveFileName, struct FClipData* InClipData);

private:
	wstring ReadFilePath;
	Assimp::Importer* Loader; // 모델을 읽어올 대상 
	const aiScene* Scene; 

	vector<struct FBoneData*> Bones;
	vector<struct FMeshData*> Meshes;
	vector<struct FMaterialData*> Materials;
};
