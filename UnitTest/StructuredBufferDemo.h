#pragma once

#include "Systems/IExecutable.h"

struct CS_InputDesc
{
	FVector Position;
	FMatrix World; 

	FColor Color; 
};

struct CS_OutputDesc
{
	FVector Position;

	FColor Color; 
};

class CStructuredBufferDemo: public IExecutable
{
public:
	void Initialize();
	void Destroy(); 
	void Tick(); 
	void Render(); 

private:
	CShader* ComputeShader; 
	CStructuredBuffer* ComputeBuffer; 

	CS_InputDesc* InputDatas;
	CS_OutputDesc* OutputDatas;

};