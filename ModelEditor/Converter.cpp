#include "Pch.h"
#include "Converter.h"
#include "Types.h"

#include <fstream>

CConverter::CConverter()
{
	Loader = new Assimp::Importer();
}

CConverter::~CConverter()
{
	Delete(Loader); 
}

void CConverter::ReadFile(wstring InFileName, float InGlobalScale)
{
	ReadFilePath = L"../../_Assets/" + InFileName;
	Loader->SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, InGlobalScale);

	Scene = Loader->ReadFile
	(
		CString::ToString(ReadFilePath).c_str(),
		aiProcess_ConvertToLeftHanded
		| aiProcess_Triangulate 
		| aiProcess_GenUVCoords 
		| aiProcess_GenNormals 
		| aiProcess_CalcTangentSpace
		| aiProcess_GenBoundingBoxes
		| aiProcess_GlobalScale
	);

	Assert(Scene != nullptr, "모델 정상 로드 않됨");
}

void CConverter::ExportMaterial(wstring InSaveFileName)
{
	InSaveFileName = L"../../Models/" + InSaveFileName + L".material";

	ReadMaterials(); 
	WriteMaterial(InSaveFileName);
}

void CConverter::ReadMaterials()
{
	printf("mNumMaterials : %d\n", Scene->mNumMaterials);
	
	for (UINT i = 0; i < Scene->mNumMaterials; i++)
	{
		aiMaterial* material = Scene->mMaterials[i]; 
		FMaterialData* data = new FMaterialData(); 

		data->Name = material->GetName().C_Str(); 
		data->ShaderName = ""; 

		aiColor4D color; 

		// Material의 속성가져오기
		// Key들이 정리됨. 
		material->Get(AI_MATKEY_COLOR_AMBIENT, color); 
		data->Ambient = FColor(color.r, color.g, color.b, color.a);

		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		data->Diffuse= FColor(color.r, color.g, color.b, color.a);

		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->Get(AI_MATKEY_SHININESS, color.a);
		data->Specular = FColor(color.r, color.g, color.b, color.a); 

		material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		data->Emissive= FColor(color.r, color.g, color.b, color.a);

		aiString textureFile;

		material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFile); 
		data->DiffuseFile = textureFile.C_Str(); 

		material->GetTexture(aiTextureType_SPECULAR, 0, &textureFile);
		data->SpecularFile = textureFile.C_Str();

		material->GetTexture(aiTextureType_NORMALS, 0, &textureFile);
		data->NormalFile = textureFile.C_Str();

		Materials.push_back(data); 
	}
}

void CConverter::WriteMaterial(wstring InSaveFileName)
{
	string folderName = CString::ToString(CPath::GetDirectoryName(InSaveFileName)); 
	string fileName = CString::ToString(CPath::GetFileName(InSaveFileName)); 

	CPath::CreateFolders(folderName); 

	Json::Value root; 

	for (FMaterialData* data : Materials)
	{
		Json::Value value; 
		value["00_Draw"] = true; 
		value["01_Technique"] = 0; 
		value["02_Pass"] = 0;
		value["03_Ambient"] = CString::ToColor(data->Ambient);
		value["04_Diffuse"] = CString::ToColor(data->Diffuse);
		value["05_Specular"] = CString::ToColor(data->Specular);
		value["06_Emissive"] = CString::ToColor(data->Emissive);
		value["07_DiffuseMap"] = SaveTexture(folderName, data->DiffuseFile);
		value["08_SpecularMap"] = SaveTexture(folderName, data->SpecularFile);
		value["09_NormalMap"] = SaveTexture(folderName, data->NormalFile);
		root[data->Name.c_str()] = value;

		Delete(data);
	}

	fileName = "../../_Materials/" + fileName; 

	Json::StyledWriter writer; 
	string str = writer.write(root);

	ofstream stream; 
	stream.open(fileName); 
	stream << str; 
	stream.close(); 
}

string CConverter::SaveTexture(string InSaveFolder, string InFileName)
{
	CheckTrueResult(InFileName.length() < 1, "");
	CheckTrueResult(InSaveFolder.length() < 1, "");

	string fileName = CPath::GetFileName(InFileName); 
	const aiTexture* texture = Scene->GetEmbeddedTexture(InFileName.c_str());

	if (texture != nullptr)
	{
		if (texture->mHeight < 1)
		{
			CBinaryWriter writer; 
			writer.Open(CString::ToWString(InSaveFolder + fileName));
			writer.ToByte(texture->pcData, texture->mWidth);
			writer.Close(); 

			return InSaveFolder + fileName; 
		}

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = texture->mWidth;
		desc.Height = texture->mHeight;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource;
		ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
		subResource.pSysMem = texture->pcData;

		ID3D11Texture2D* saveTexture;
		Check(CD3D::Get()->GetDevice()->CreateTexture2D(&desc, &subResource, &saveTexture));

		D3DX11SaveTextureToFileA(CD3D::Get()->GetDeviceContext(), saveTexture, D3DX11_IFF_PNG, (InSaveFolder + fileName).c_str());

		return InSaveFolder + fileName;
	}

	string directory = CPath::GetDirectoryName(CString::ToString(ReadFilePath));
	string origin = directory + InFileName;
	CString::Replace(&origin, "\\", "/"); 

	CheckFalseResult(CPath::ExistFile(origin), ""); 

	string path = InSaveFolder + fileName;
	CopyFileA(origin.c_str(), path.c_str(), FALSE); 

	return InSaveFolder + CPath::GetFileName(path);
}
