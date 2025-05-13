#include "Framework.h"
#include "BinaryFile.h"

CBinaryWriter::CBinaryWriter()
{

}

CBinaryWriter::~CBinaryWriter()
{
	Close();
}

void CBinaryWriter::Open(wstring InFilePath, UINT InOption)
{
	assert(InFilePath.length() > 0);

	FileHandle = CreateFile
	(
		InFilePath.c_str(),
		GENERIC_WRITE,
		0,
		nullptr,
		InOption,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
	assert(FileHandle != INVALID_HANDLE_VALUE);
}

void CBinaryWriter::Close()
{
	CheckNull(FileHandle);

	CloseHandle(FileHandle);
	FileHandle = nullptr;
}

void CBinaryWriter::ToInt(int InData)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InData, sizeof(int), &size, nullptr);
}

void CBinaryWriter::ToUInt(UINT InData)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InData, sizeof(UINT), &size, nullptr);
}

void CBinaryWriter::ToFloat(float InData)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InData, sizeof(float), &size, nullptr);
}

void CBinaryWriter::ToMatrix(FMatrix& InData)
{
	DWORD size = 0;

	const float* m = InData;
	WriteFile(FileHandle, m, sizeof(FMatrix), &size, nullptr);

	assert(sizeof(FMatrix) == size);
}

void CBinaryWriter::ToString(const string& InData)
{
	ToUInt(InData.size());


	DWORD size = 0;

	const char* str = InData.c_str();
	WriteFile(FileHandle, str, InData.size(), &size, nullptr);

	assert(InData.size() == size);
}

void CBinaryWriter::ToByte(void* InData, UINT InDataSize)
{
	DWORD size = 0;

	WriteFile(FileHandle, InData, InDataSize, &size, nullptr);
	assert(InDataSize == size);
}

//-----------------------------------------------------------------------------

CBinaryReader::CBinaryReader()
{

}

CBinaryReader::~CBinaryReader()
{
	Close();
}

void CBinaryReader::Open(wstring InFilePath)
{
	assert(InFilePath.length() > 0);

	FileHandle = CreateFile
	(
		InFilePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
	assert(FileHandle != INVALID_HANDLE_VALUE);
}

void CBinaryReader::Close()
{
	CheckNull(FileHandle);

	CloseHandle(FileHandle);
	FileHandle = nullptr;
}

int CBinaryReader::FromInt()
{
	int temp = 0;

	DWORD size = 0;
	ReadFile(FileHandle, &temp, sizeof(int), &size, nullptr);

	return temp;
}

UINT CBinaryReader::FromUInt()
{
	UINT temp = 0;

	DWORD size = 0;
	ReadFile(FileHandle, &temp, sizeof(UINT), &size, nullptr);

	return temp;
}

float CBinaryReader::FromFloat()
{
	float temp = 0.0f;

	DWORD size = 0;
	ReadFile(FileHandle, &temp, sizeof(float), &size, nullptr);

	return temp;
}

FMatrix CBinaryReader::FromMatrix()
{
	float temp[16];

	DWORD size = 0;
	ReadFile(FileHandle, temp, sizeof(FMatrix), &size, nullptr);
	assert(size == sizeof(FMatrix));

	FMatrix result;
	memcpy(&result, temp, sizeof(FMatrix));

	return result;
}

string CBinaryReader::FromString()
{
	UINT length = FromUInt();
	char* temp = new char[length + 1];

	DWORD size = 0;
	ReadFile(FileHandle, temp, sizeof(char) * length, &size, nullptr);
	assert(size == (sizeof(char) * length));

	temp[length] = '\0';

	string result(temp);
	DeleteArray(temp);

	return result;
}

void CBinaryReader::FromByte(void** OutData, UINT InDataSize)
{
	DWORD size = 0;
	ReadFile(FileHandle, *OutData, InDataSize, &size, nullptr);
	//assert(size == InDataSize);
}
