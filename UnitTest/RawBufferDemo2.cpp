#include "Pch.h"
#include "RawBufferDemo2.h"
#include <fstream>

void CRawBufferDemo2::Initialize()
{
	Case1();
	Case2();
	Case3();
}


void CRawBufferDemo2::Case1()
{
	CShader* shader = new CShader(L"RawBuffer2.fx");

	UINT count = 10 * 8 * 3;

	// 리턴을 받아낼 구조체 
	struct Output
	{
		UINT Index;
		UINT Id[3];
		float Value;
	};

	CRawBuffer* rawBuffer = new CRawBuffer(nullptr, 0, sizeof(Output) * count);

	shader->AsUAV("Output")->SetUnorderedAccessView(*rawBuffer);
	shader->Dispatch(0, 0, 1, 1, 1);

	Output* output = new Output[count];
	rawBuffer->GetOutputData(output);

	ofstream file;
	file.open("../Case1.csv");

	for (UINT i = 0; i < count; i++)
	{
		file << output[i].Index << ",";
		file << output[i].Id[0] << ",";
		file << output[i].Id[1] << ",";
		file << output[i].Id[2] << ",";
		file << output[i].Value << endl;
	}

	file.close();
}

void CRawBufferDemo2::Case2()
{
	CShader* shader = new CShader(L"RawBuffer2.fx");

	UINT count = (3 * 2 * 1) * (5 * 4 * 1); // x 방향으로 3개의 그룹 

	// 리턴을 받아낼 구조체 
	struct Output
	{
		UINT GroupID[3];
		UINT Index;
		UINT ThreadID[3];
		UINT DispatchID[3];
	};

	CRawBuffer* rawBuffer = new CRawBuffer(nullptr, 0, sizeof(Output) * count);

	shader->AsUAV("Output")->SetUnorderedAccessView(*rawBuffer);
	shader->Dispatch(0, 1, 3, 2, 1);

	Output* output = new Output[count];
	rawBuffer->GetOutputData(output);

	ofstream file;
	file.open("../Case2.csv");

	for (UINT i = 0; i < count; i++)
	{
		file << output[i].GroupID[0] << ",";	// x
		file << output[i].GroupID[1] << ",";	// y 
		file << output[i].GroupID[2] << ",";	// z

		file << output[i].Index << ",";

		file << output[i].ThreadID[0] << ",";	// x
		file << output[i].ThreadID[1] << ",";	// y
		file << output[i].ThreadID[2] << ",";	// z

		file << output[i].DispatchID[0] << ",";	// x
		file << output[i].DispatchID[1] << ",";	// y
		file << output[i].DispatchID[2] << endl; // z
	}

	file.close();
}
void CRawBufferDemo2::Case3()
{
	CShader* shader = new CShader(L"RawBuffer2.fx");

	UINT count = (5 * 4 * 1)* (3 * 2 * 1) ; // x 방향으로 3개의 그룹 


#pragma pack(push, 1)
	struct FInput {
		UINT Index;
		float Value;
	};
#pragma pack(pop)

	static_assert(sizeof(FInput) == 8, "FInput must be 8 bytes");
	FInput* input = new FInput[count];

	for (UINT i = 0; i < count; i++)
	{
		input[i].Index = i;
		input[i].Value = FMath::Random((float)0, (float)count);
	}

	// 리턴을 받아낼 구조체 
#pragma pack(push, 1)
	struct Output
	{
		UINT GroupID[3];

		UINT ThreadID[3];
		UINT DispatchID[3];
		UINT Index;

		UINT TotalIndex;
		float Value;
		float Value2;
	};
#pragma pack(pop)
	static_assert(sizeof(Output) == 52, "Output struct must be 52 bytes!");

	CRawBuffer* rawBuffer = new CRawBuffer(input, sizeof(FInput) * count, sizeof(Output) * count);

	shader->AsSRV("Input")->SetResource(*rawBuffer);
	shader->AsUAV("Output")->SetUnorderedAccessView(*rawBuffer);
	shader->Dispatch(0, 2, 3, 2, 1);

	CD3D::Get()->GetDeviceContext()->Flush(); // GPU 강제 sync

	Output* output = new Output[count];
	rawBuffer->GetOutputData(output);

	ofstream file;
	file.open("../Case3.csv");

	for (UINT i = 0; i < count; i++)
	{
		file << output[i].GroupID[0] << ",";	// x
		file << output[i].GroupID[1] << ",";	// y 
		file << output[i].GroupID[2] << ",";	// z

		file << output[i].Index << ",";

		file << output[i].ThreadID[0] << ",";	// x
		file << output[i].ThreadID[1] << ",";	// y
		file << output[i].ThreadID[2] << ",";	// z

		file << output[i].DispatchID[0] << ",";	// x
		file << output[i].DispatchID[1] << ",";	// y
		file << output[i].DispatchID[2] << ","; // z

		file << output[i].TotalIndex << ",";
		file << output[i].Value << ",";
		file << output[i].Value2 << endl;
	}

	file.close();
}
