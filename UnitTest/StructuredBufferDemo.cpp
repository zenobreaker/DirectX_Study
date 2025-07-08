#include "Pch.h"
#include "StructuredBufferDemo.h"

void CStructuredBufferDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(21, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(0, 5.5f, -20));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);

	InputDatas = new CS_InputDesc[1024];
	for (UINT i = 0; i < 1024; i++)
	{
		InputDatas[i].Position = FVector::Zero;
		
		FVector pos = FVector::Zero;
		pos.X = FMath::Random(-5.0f, 5.0f);
		pos.Y = 0.0f; 
		pos.Z = FMath::Random(-5.0f, 5.0f);

		InputDatas[i].World = FMatrix::CreateWorld(pos, FVector::Forward, FVector::Up);


		FColor color = FColor(1, 1, 1, 1);
		color.R = FMath::Random(0.0f, 1.0f);
		color.G = FMath::Random(0.0f, 1.0f);
		color.B = FMath::Random(0.0f, 1.0f);

		InputDatas[i].Color = color;
	}

	OutputDatas = new CS_OutputDesc[1024];

	ComputeShader = new CShader(L"StructuredBuffer.fx");
	ComputeBuffer = new CStructuredBuffer(InputDatas, sizeof(CS_InputDesc), 1024, sizeof(CS_OutputDesc), 1024);

	ComputeShader->AsSRV("Input")->SetResource(*ComputeBuffer);
	ComputeShader->AsUAV("Output")->SetUnorderedAccessView(*ComputeBuffer);

	ComputeShader->Dispatch(0, 0, 1, 1, 1);

	ComputeBuffer->GetOutputData(OutputDatas);
}

void CStructuredBufferDemo::Destroy()
{
	Delete(ComputeShader);
	Delete(ComputeBuffer);
}

void CStructuredBufferDemo::Tick()
{
}

void CStructuredBufferDemo::Render()
{
	for (UINT i = 0; i < 1024; i++)
	{
		FVector position = OutputDatas[i].Position;

		FVector start = position;
		start.Y = 0.0f;

		FVector end = position;
		end.Y = 5.0f;

		CRenderLine::Get()->Draw(start, end, OutputDatas[i].Color);
	}
}
