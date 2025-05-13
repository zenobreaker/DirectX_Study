#pragma once

class CBinaryWriter
{
public:
	CBinaryWriter();
	~CBinaryWriter();

	void Open(wstring InFilePath, UINT InOption = CREATE_ALWAYS);
	void Close();

public:
	void ToInt(int InData);
	void ToUInt(UINT InData);
	void ToFloat(float InData);

	void ToMatrix(FMatrix& InData);

	void ToString(const string& InData);
	void ToByte(void* InData, UINT InDataSize);

private:
	HANDLE FileHandle = nullptr;
};

//-----------------------------------------------------------------------------

class CBinaryReader
{
public:
	CBinaryReader();
	~CBinaryReader();

	void Open(wstring InFilePath);
	void Close();

public:
	int FromInt();
	UINT FromUInt();
	float FromFloat();

	FMatrix FromMatrix();
	string FromString();

	void FromByte(void** OutData, UINT InDataSize);

private:
	HANDLE FileHandle = nullptr;
};

