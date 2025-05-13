#pragma once

class CVertexBuffer
{
public:
	CVertexBuffer(void* InData, UINT InCount, UINT InStride, UINT InSlot = 0, bool InCpuWrite = false, bool InGpuWrite = false);
	~CVertexBuffer();

	operator ID3D11Buffer* () { return Buffer; }
	operator const ID3D11Buffer* () { return Buffer; }

	UINT GetCount() { return Count; }
	UINT GetStride() { return Stride; }

	void Mapping();
	void Render();

private:
	ID3D11Buffer* Buffer;

	void* Data;
	UINT Count;
	UINT Stride;
	UINT Slot;

private:
	bool bCpuWrite;
	bool bGpuWrite;
};

//------------------------------------------------------------------------------

class CIndexBuffer
{
public:
	CIndexBuffer(UINT* InData, UINT InCount);
	~CIndexBuffer();

	UINT GetCount() { return Count; }

	void Render();

private:
	ID3D11Buffer* Buffer;

	UINT* Data;
	UINT Count;
};

//------------------------------------------------------------------------------

class CConstantBuffer
{
public:
	CConstantBuffer(CShader* InShader, string InName, void* InData, UINT InDataSize);
	~CConstantBuffer();

	void Render();

private:
	CShader* Shader;
	string Name;

	ID3D11Buffer* Buffer;
	ID3DX11EffectConstantBuffer* sBuffer;

	void* Data;
	UINT DataSize;
};