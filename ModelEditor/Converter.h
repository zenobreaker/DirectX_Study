#pragma once


class CConverter
{
public:
	CConverter(); 
	~CConverter(); 

	void ReadFile(wstring InFileName, float InGlobalScale = 1.0f); 

public:
	void ExportMaterial(wstring InSaveFileName);

private:
	void ReadMaterials(); 
	void WriteMaterial(wstring InSaveFileName); 
	
	string SaveTexture(string InSaveFolder, string InFileName);

private:
	wstring ReadFilePath;
	Assimp::Importer* Loader; // 모델을 읽어올 대상 
	const aiScene* Scene; 

	vector<struct FMaterialData*> Materials;
};
