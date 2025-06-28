#pragma once
#include "Pch.h"

struct FMaterialData
{
	string Name; 
	string ShaderName; 

	FColor Ambient;
	FColor Diffuse; 
	FColor Specular; 
	FColor Emissive;

	string DiffuseFile;
	string SpecularFile; 
	string NormalFile; 
};

struct FBoneData
{
	UINT Index;
	string Name;

	int Parent;
	FMatrix Transform;
	FMatrix OffsetTransform; // “BindPose 상태를 애니메이션 포즈로 바꿔주는 교정 행렬”
};

struct FMeshData
{
	string Name;
	string MaterialName; 
	int BoneIndex; 

	vector<FVertexModel> Vertices; 
	vector<UINT> Indices; 
};

struct FClipNodeData
{
	string BoneName;

	vector<CModelAnimation::FFrameVector> PositionKeys;
	vector<CModelAnimation::FFrameVector> ScalingKeys;
	vector<CModelAnimation::FFrameQuat> RotationKeys;
};

struct FClipData
{
	string Name;

	float Duration;
	float TickersPerSecond;

	vector<FClipNodeData*> NodeDatas;
};