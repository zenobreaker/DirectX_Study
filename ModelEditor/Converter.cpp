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

void CConverter::ExportMesh(wstring InSaveFileName)
{
	InSaveFileName = L"../../_Models/" + InSaveFileName + L".mesh"; 

	ReadBoneData(Scene->mRootNode, 0, -1); 
	ReadSkinData(); 

	WriteMeshData(InSaveFileName);
}

void CConverter::ReadMeshData()
{
	for (UINT i = 0; i < Scene->mNumMeshes; i++)
	{
		FMeshData* data = new FMeshData(); 

		aiMesh* mesh = Scene->mMeshes[i];
		data->Name = mesh->mName.C_Str(); 

		UINT materialIndex = mesh->mMaterialIndex; 
		aiMaterial* material = Scene->mMaterials[materialIndex];
		data->MaterialName = material->GetName().C_Str(); 
		
		for (UINT v = 0; v < mesh->mNumVertices; v++)
		{
			FVertexModel vertex; 

			memcpy_s(&vertex.Position, sizeof(FVector), &mesh->mVertices[v], sizeof(FVector));

			if (mesh->HasTextureCoords(0))
				memcpy_s(&vertex.Uv, sizeof(FVector2D), &mesh->mTextureCoords[0][v], sizeof(FVector2D));

			if (mesh->HasVertexColors(0))
				memcpy_s(&vertex.Color, sizeof(FColor), &mesh->mColors[0][v], sizeof(FColor));

			if (mesh->HasNormals())
				memcpy_s(&vertex.Normal, sizeof(FVector), &mesh->mNormals[v], sizeof(FVector));

			if (mesh->HasTangentsAndBitangents())
				memcpy_s(&vertex.Tangent, sizeof(FVector), &mesh->mTangents[v], sizeof(FVector));

			data->Vertices.push_back(vertex);
		}

		for (UINT f = 0; f < mesh->mNumFaces; f++)
		{
			aiFace& face = mesh->mFaces[f];

			for (UINT k = 0; k < face.mNumIndices; k++)
				data->Indices.push_back(face.mIndices[k]);
		}

		Meshes.push_back(data);
	}
}

void CConverter::ReadBoneData(aiNode* InNode, UINT InIndex, int InParent)
{
	FBoneData* bone = new FBoneData(); 
	bone->Index = InIndex;
	bone->Parent = InParent;
	bone->Name = InNode->mName.C_Str(); 

	memcpy_s(bone->Transform, sizeof(FMatrix), InNode->mTransformation[0], sizeof(FMatrix));
	bone->Transform = FMatrix::Transpose(bone->Transform);

	FMatrix parent; 
	if (InParent < 0)
		parent = FMatrix::Identity;
	else
		parent = Bones[InParent]->Transform;

	bone->Transform = bone->Transform * parent; //(L-World * Parent)
	Bones.push_back(bone); 

	ReadMeshData(InNode, InIndex);

	for (UINT i = 0; i < InNode->mNumChildren; i++)
		ReadBoneData(InNode->mChildren[i], Bones.size(), InIndex);
}

void CConverter::ReadMeshData(aiNode* InNode, UINT InBoneIndex)
{
	CheckTrue(InNode->mNumMeshes < 1);

	for (UINT i = 0; i < InNode->mNumMeshes; i++)
	{
		FMeshData* data = new FMeshData(); 

		UINT index = InNode->mMeshes[i];
		aiMesh* mesh = Scene->mMeshes[index]; 

		data->Name = mesh->mName.C_Str(); 

		UINT materialIndex = mesh->mMaterialIndex;
		aiMaterial* material = Scene->mMaterials[materialIndex]; 
		data->MaterialName = material->GetName().C_Str(); 

		data->BoneIndex = InBoneIndex; 

		for (UINT v = 0; v < mesh->mNumVertices; v++)
		{
			FVertexModel vertex; 

			memcpy_s(&vertex.Position, sizeof(FVector), &mesh->mVertices[v], sizeof(FVector));

			if (mesh->HasTextureCoords(0))
				memcpy_s(&vertex.Uv, sizeof(FVector2D), &mesh->mTextureCoords[0][v], sizeof(FVector2D));

			if (mesh->HasVertexColors(0))
				memcpy_s(&vertex.Color, sizeof(FColor), &mesh->mColors[0][v], sizeof(FColor));

			if (mesh->HasNormals())
				memcpy_s(&vertex.Normal, sizeof(FVector), &mesh->mNormals[v], sizeof(FVector));

			if (mesh->HasTangentsAndBitangents())
				memcpy_s(&vertex.Tangent, sizeof(FVector), &mesh->mTangents[v], sizeof(FVector));

			data->Vertices.push_back(vertex);
		}
		for (UINT f = 0; f < mesh->mNumFaces; f++)
		{
			aiFace& face = mesh->mFaces[f];

			for (UINT k = 0; k < face.mNumIndices; k++)
				data->Indices.push_back(face.mIndices[k]);
		}

		Meshes.push_back(data);
	}
}

void CConverter::ReadSkinData()
{
	for (UINT i = 0; i < Scene->mNumMeshes; i++)
	{
		aiMesh* mesh = Scene->mMeshes[i];

		if (mesh->HasBones() == false)
			continue; 

		for (UINT b = 0; b < mesh->mNumBones; b++)
		{
			aiBone* bone = mesh->mBones[b]; 
			string boneName = bone->mName.C_Str(); 

			UINT index = 0; 
			for (UINT boneIndex = 0; boneIndex < Bones.size(); boneIndex++)
			{
				if (Bones[boneIndex]->Name == boneName)
				{
					index = (int)boneIndex;

					break; 
				}
			}

			FMatrix offset; 
			memcpy_s(offset, sizeof(FMatrix), bone->mOffsetMatrix[0], sizeof(FMatrix));
			Bones[index]->OffsetTransform = FMatrix::Transpose(offset); 

			for (UINT w = 0; w < bone->mNumWeights; w++)
			{
				UINT id = bone->mWeights[w].mVertexId;
				float weight = bone->mWeights[w].mWeight;

				FMeshData* meshData = Meshes[i];

				FVector4& indices = meshData->Vertices[id].Indices;
				FVector4& weights = meshData->Vertices[id].Weights;

				int v; 
				for (v = 0; v < 4; v++)
				{
					if (indices.V[v] <= 0.0f)
					{
						indices.V[v] = (float)index; 
						weights.V[v] = weight;

						break; 
					}
				}//for(v)
			}//for(w)
		}
	}//for(i)
}

void CConverter::WriteMeshData(wstring InSaveFileName)
{
	CPath::CreateFolders(CPath::GetDirectoryName(InSaveFileName));

	CBinaryWriter* w = new CBinaryWriter();
	w->Open(InSaveFileName); 

	w->ToUInt(Bones.size());
	for (FBoneData* data : Bones)
	{
		w->ToUInt(data->Index);
		w->ToString(data->Name); 

		w->ToInt(data->Parent); 
		w->ToMatrix(data->Transform);
		w->ToMatrix(data->OffsetTransform);

		Delete(data);
	}

	w->ToUInt(Meshes.size());
	for (FMeshData* data : Meshes)
	{
		w->ToString(data->Name);
		w->ToString(data->MaterialName);
		w->ToUInt(data->BoneIndex);

		w->ToUInt(data->Vertices.size());
		w->ToByte(&data->Vertices[0], sizeof(FVertexModel) * data->Vertices.size());

		w->ToUInt(data->Indices.size());
		w->ToByte(&data->Indices[0], sizeof(UINT) * data->Indices.size());

		Delete(data);
	}

	w->Close();
	Delete(w);
}

void CConverter::ExportMaterial(wstring InSaveFileName)
{
	InSaveFileName = L"../../_Models/" + InSaveFileName + L".material";

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

void CConverter::ExportAnimation(wstring InSaveFileName, int InClipIndex)
{
	FClipData* clipdata = nullptr; 
	InSaveFileName = L"../../_Models/" + InSaveFileName + L".animation";

	clipdata = ReadClipData(Scene->mAnimations[InClipIndex]);
	WriteClipData(InSaveFileName, clipdata);
}

FClipData* CConverter::ReadClipData(aiAnimation* InAnimation)
{
	FClipData* clipData = new FClipData();

	clipData->Name = InAnimation->mName.C_Str();
	clipData->Duration = (float)InAnimation->mDuration;
	clipData->TickersPerSecond = (float)InAnimation->mTicksPerSecond;

	for (UINT i = 0; i < InAnimation->mNumChannels; i++)
	{
		aiNodeAnim* nodeAnim = InAnimation->mChannels[i];

		FClipNodeData* nodeData = new FClipNodeData();
		nodeData->BoneName = nodeAnim->mNodeName.C_Str();


		//PositionKeys
		for (UINT keyIndex = 0; keyIndex < nodeAnim->mNumPositionKeys; keyIndex++)
		{
			const aiVectorKey& key = nodeAnim->mPositionKeys[keyIndex];

			CModelAnimation::FFrameVector vectorData;
			vectorData.Time = (float)key.mTime;
			memcpy(&vectorData.Value, &key.mValue, sizeof(FVector));

			nodeData->PositionKeys.push_back(vectorData);
		}

		//ScalingKeys
		for (UINT keyIndex = 0; keyIndex < nodeAnim->mNumScalingKeys; keyIndex++)
		{
			const aiVectorKey& key = nodeAnim->mScalingKeys[keyIndex];

			CModelAnimation::FFrameVector vectorData;
			vectorData.Time = (float)key.mTime;
			memcpy(&vectorData.Value, &key.mValue, sizeof(FVector));

			nodeData->ScalingKeys.push_back(vectorData);
		}

		//RotationKeys
		for (UINT keyIndex = 0; keyIndex < nodeAnim->mNumRotationKeys; keyIndex++)
		{
			const aiQuatKey& key = nodeAnim->mRotationKeys[keyIndex];

			CModelAnimation::FFrameQuat quatData;
			quatData.Time = (float)key.mTime;

			quatData.Value.X = key.mValue.x;
			quatData.Value.Y = key.mValue.y;
			quatData.Value.Z = key.mValue.z;
			quatData.Value.W = key.mValue.w;

			nodeData->RotationKeys.push_back(quatData);
		}

		//printf("%d, %s, %d, %d, %d\n", (int)clipData->Duration, nodeData->BoneName.c_str(), nodeData->PositionKeys.size(), nodeData->RotationKeys.size(), nodeData->ScalingKeys.size());
		clipData->NodeDatas.push_back(nodeData);
	}//for(i)

	//printf("------------------------------------------------------------\n");

	return clipData;
}

void CConverter::WriteClipData(wstring InSaveFileName, FClipData* InClipData)
{
	CPath::CreateFolders(CPath::GetDirectoryName(InSaveFileName));

	CBinaryWriter* w = new CBinaryWriter();
	w->Open(InSaveFileName);

	w->ToString(InClipData->Name);

	w->ToFloat(InClipData->Duration);
	w->ToFloat(InClipData->TickersPerSecond);

	w->ToUInt(InClipData->NodeDatas.size());
	for (FClipNodeData* nodeData : InClipData->NodeDatas)
	{
		w->ToString(nodeData->BoneName);


		UINT count = 0;

		count = nodeData->PositionKeys.size();
		w->ToUInt(count);
		w->ToByte(&nodeData->PositionKeys[0], sizeof(CModelAnimation::FFrameVector) * count);

		count = nodeData->ScalingKeys.size();
		w->ToUInt(count);
		w->ToByte(&nodeData->ScalingKeys[0], sizeof(CModelAnimation::FFrameVector) * count);

		count = nodeData->RotationKeys.size();
		w->ToUInt(count);
		w->ToByte(&nodeData->RotationKeys[0], sizeof(CModelAnimation::FFrameQuat) * count);

		Delete(nodeData);
	}

	Delete(InClipData);

	w->Close();
	Delete(w);
}
