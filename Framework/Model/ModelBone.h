#pragma once

class CModelBone
{
public:
	friend class CMeshRender;
	friend class CAnimRender;

private:
	CModelBone();
	~CModelBone();

public:
	string GetName() { return Name; }
	int GetParentIndex() { return ParentIndex; }

	const FMatrix& GetTransform() { return Transform; }
	const FMatrix& GetOffsetTransform() { return OffsetTransform; }

private:
	UINT Index = 0;
	string Name = "";

	int ParentIndex = -1;
	CModelBone* Parent = nullptr;

	FMatrix Transform;
	FMatrix OffsetTransform;
	vector<CModelBone*> Children;
};