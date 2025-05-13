#pragma once

struct FProjectorVP
{
	int TextureIndex = -1;
	float Padding[3];

	FColor Color;
	FMatrix View;
	FMatrix Projection;
};

struct FProjector
{
	int TextureIndex = -1;
	FColor Color = FColor(0, 0, 0, 0);

	FVector Position = FVector::Zero;
	FVector Rotation = FVector::Zero;

	float Width = 1.0f;
	float Height = 1.0f;
	float Near = 1.0f;
	float Far = 100.0f;
	
	//FOV가 0일 경우 Orthographic으로 간주
	float FOV = 0.0f; 

private:
	friend class CProjector;

private:
	FProjectorVP* ProjectorVP = nullptr;

private:
	void ApplyData();
};

struct FProjectorDesc
{
	UINT Count = 0;
	float Padding[3];

	FProjectorVP VPs[MAX_PROJECTOR_COUNT];
};

class CProjector
{
public:
	static void Create();
	static void Destroy();

	static CProjector* Get();

private:
	CProjector();
	~CProjector();

public:
	void Tick();

public:
	const vector<wstring>& GetTextureFiles() { return TextureFiles; }
	
public:
	FProjectorDesc* GetData() { return &Data; }

private:
	static CProjector* Instance;

public:
	void AddTexture(wstring InFile);
	void AddProjector(const FProjector& InData);

private:
	bool bShowGUI = false;

private:
	vector<wstring> TextureFiles;

private:
	FProjector Projectors[MAX_PROJECTOR_COUNT];
	FProjectorDesc Data;
};