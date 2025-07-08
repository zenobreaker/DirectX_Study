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

//------------------------------------------------------------------------------

class CCsResource
{
public:
	CCsResource();
	virtual ~CCsResource();

public:
	operator ID3D11UnorderedAccessView* () { return UAV; }
	operator const ID3D11UnorderedAccessView* () { return UAV; }

	operator ID3D11ShaderResourceView* () { return SRV; }
	operator const ID3D11ShaderResourceView* () { return SRV; }

protected:
	virtual void CreateInput() {};
	virtual void CreateSRV() = 0;

	virtual void CreateOutput() = 0;
	virtual void CreateUAV() = 0;

	virtual void CreateResult() = 0;

protected:
	void CreateBuffer();

protected:
	ID3D11Resource* Input = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;

	ID3D11Resource* Output = nullptr;
	ID3D11UnorderedAccessView* UAV = nullptr;

	ID3D11Resource* Result = nullptr; // 결과 복사본
};

class CRawBuffer : public CCsResource
{
public:
	CRawBuffer(void* InInputData, UINT InInputSize, UINT InOutputSize);
	 ~CRawBuffer();

private:

	void CreateInput() override;
	void CreateSRV() override;
	void CreateOutput() override;
	void CreateUAV() override;
	void CreateResult() override;


public:
	void SetInputData(void* InData);
	void GetOutputData(void* OutData);

private:
	void* InputData = nullptr;

	UINT InputSize = 0;
	UINT OutputSize = 0;
};

//------------------------------------------------------------------------------

class CTextureBuffer : public CCsResource
{
public:
	CTextureBuffer(ID3D11Texture2D* InSource);
	~CTextureBuffer();

private:
	void CreateSRV() override;
	void CreateOutput() override;
	void CreateUAV() override;
	void CreateResult() override;

public:
	UINT GetWidth() { return Width; }
	UINT GetHeight() { return Height; }
	UINT GetArraySize() { return ArraySize; }
	DXGI_FORMAT GetFormat() { return Format; }

	ID3D11Texture2D* GetOutput() { return (ID3D11Texture2D*)Output; }
	ID3D11ShaderResourceView* GetOutputSRV() { return OutputSRV; }

private:
	UINT Width;
	UINT Height; 
	UINT ArraySize; 
	DXGI_FORMAT Format; 

	ID3D11ShaderResourceView* OutputSRV; 
};

//-----------------------------------------------------------------------------
class CStructuredBuffer : public CCsResource
{
public:
	// Output = 0이면 Input과 같은 자료형 사용을 의미
	CStructuredBuffer(void* InInputData, UINT InInputStride, UINT InInputCount, UINT InOutputStride = 0, UINT InOutputCount = 0);
	~CStructuredBuffer();

private:

	void CreateInput() override;
	void CreateSRV() override;
	void CreateOutput() override;
	void CreateUAV() override;
	void CreateResult() override;


public:
	void SetInputData(void* InData);
	void GetOutputData(void* OutData);

public:
	UINT GetInputByteWidth() { return InputStride * InputCount; }
	UINT GetOutputByteWidth() { return OutputStride* OutputCount; }

private:
	CShader* Shader; 

	void* InputData = nullptr;

	UINT InputStride = 0; // 구조체의 크기
	UINT InputCount = 0;


	UINT OutputStride = 0;
	UINT OutputCount = 0;
};