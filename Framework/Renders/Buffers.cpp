#include "Framework.h"
#include "Buffers.h"

CVertexBuffer::CVertexBuffer(void* InData, UINT InCount, UINT InStride, UINT InSlot, bool InCpuWrite, bool InGpuWrite)
	: Data(InData), Count(InCount), Stride(InStride), Slot(InSlot)
	, bCpuWrite(InCpuWrite), bGpuWrite(InGpuWrite)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = InStride * Count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (bCpuWrite == false && bGpuWrite == false)
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
	}
	else if (bCpuWrite == true && bGpuWrite == false)
	{
		//CPU - RW(Map), GPU - R

		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if (bCpuWrite == false && bGpuWrite == true)
	{
		//CPU W(UpdateSubresource), GPU - RW

		desc.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	}


	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = Data;

	Check(CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &Buffer));
}

CVertexBuffer::~CVertexBuffer()
{
	Release(Buffer);
}

void CVertexBuffer::Mapping()
{
	assert(bCpuWrite);

	D3D11_MAPPED_SUBRESOURCE subResource;
	CD3D::Get()->GetDeviceContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, Data, Stride * Count);
	}
	CD3D::Get()->GetDeviceContext()->Unmap(Buffer, 0);
}

void CVertexBuffer::Render()
{
	UINT offset = 0;

	CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(Slot, 1, &Buffer, &Stride, &offset);
}

//------------------------------------------------------------------------------

CIndexBuffer::CIndexBuffer(UINT* InData, UINT InCount)
	: Data(InData), Count(InCount)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(UINT) * Count;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = Data;

	Check(CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &Buffer));
}

CIndexBuffer::~CIndexBuffer()
{
	Release(Buffer);
}

void CIndexBuffer::Render()
{
	CD3D::Get()->GetDeviceContext()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}

//------------------------------------------------------------------------------

CConstantBuffer::CConstantBuffer(CShader* InShader, string InName, void* InData, UINT InDataSize)
	: Shader(InShader), Name(InName), Data(InData), DataSize(InDataSize)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = DataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Check(CD3D::Get()->GetDevice()->CreateBuffer(&desc, nullptr, &Buffer));


	sBuffer = Shader->AsConstantBuffer(InName);
	assert(sBuffer != nullptr);
}

CConstantBuffer::~CConstantBuffer()
{
	Release(Buffer);
}

void CConstantBuffer::Render()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	CD3D::Get()->GetDeviceContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, Data, DataSize);
	}
	CD3D::Get()->GetDeviceContext()->Unmap(Buffer, 0);

	sBuffer->SetConstantBuffer(Buffer);
}

//------------------------------------------------------------------------------

CCsResource::CCsResource()
{
}

CCsResource::~CCsResource()
{
	Release(Input);
	Release(SRV);

	Release(Output);
	Release(UAV);

	Release(Result);
}

void CCsResource::CreateBuffer()
{
	CreateInput();
	CreateSRV();

	CreateOutput();
	CreateUAV();

	CreateResult();
}

//------------------------------------------------------------------------------

CRawBuffer::CRawBuffer(void* InInputData, UINT InInputSize, UINT InOutputSize)
	: InputData(InInputData), InputSize(InInputSize), OutputSize(InOutputSize)
{
	CreateBuffer();
}

CRawBuffer::~CRawBuffer()
{
}

void CRawBuffer::CreateInput()
{
	CheckFalse(InputSize > 0);

	// 버퍼 생성
	ID3D11Buffer* buffer = nullptr;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = InputSize;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS; // 어떠한 버퍼의 형태를 결정
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = InputData;

	Check(CD3D::Get()->GetDevice()->CreateBuffer(
		&desc,
		InputData != nullptr ? &subResource : nullptr,
		&buffer));

	Input = (ID3D11Resource*)buffer;
}

void CRawBuffer::CreateSRV()
{
	CheckFalse(InputSize > 0);

	ID3D11Buffer* buffer = (ID3D11Buffer*)Input;

	D3D11_BUFFER_DESC desc;
	buffer->GetDesc(&desc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R32_TYPELESS; // 타입을 모르지만 4바이트(32비트) 
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX; // 버퍼의 확장명으로 
	srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
	srvDesc.BufferEx.NumElements = desc.ByteWidth / 4; // 실제 개수 (바이트 수로나눈 값)

	Check(CD3D::Get()->GetDevice()->CreateShaderResourceView(buffer, &srvDesc, &SRV));
}

void CRawBuffer::CreateOutput()
{
	Assert(OutputSize > 0, "잘못된 OutputSize ");

	ID3D11Buffer* buffer = nullptr;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = OutputSize;
	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS; // UAV에 연결되므로 플래그 변경
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS; // 어떠한 버퍼의 형태를 결정
	desc.Usage = D3D11_USAGE_DEFAULT; // GPU -> CPU

	Check(CD3D::Get()->GetDevice()->CreateBuffer(
		&desc,
		nullptr,
		&buffer));

	Output = (ID3D11Resource*)buffer;
}

void CRawBuffer::CreateUAV()
{
	Assert(OutputSize > 0, "잘못된 OutputSize ");

	ID3D11Buffer* buffer = (ID3D11Buffer*)Output;

	D3D11_BUFFER_DESC desc;
	buffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavDesc.Format = DXGI_FORMAT_R32_TYPELESS; // 타입을 모르지만 4바이트(32비트) 
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
	uavDesc.Buffer.NumElements = desc.ByteWidth / 4; // 실제 개수 (바이트 수로나눈 값)

	Check(CD3D::Get()->GetDevice()->CreateUnorderedAccessView(buffer, &uavDesc, &UAV) >= 0);
}

void CRawBuffer::CreateResult()
{
	Assert(OutputSize > 0, "잘못된 OutputSize ");

	D3D11_BUFFER_DESC desc;
	((ID3D11Buffer*)Output)->GetDesc(&desc);

	// 이미 desc에 있으므로 width 필요 없다 .
	desc.BindFlags = 0;		// 결과는 아무것도 모르므로 0 값 
	desc.MiscFlags = 0;		// "
	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ; //CPU에서 읽을 것이므로 해당 플래그 키기 

	ID3D11Buffer* buffer = nullptr;
	Check(CD3D::Get()->GetDevice()->CreateBuffer(
		&desc,
		nullptr,
		&buffer));

	Result = (ID3D11Resource*)buffer;
}

void CRawBuffer::SetInputData(void* InData)
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	// 이미 맵이 걸려 있는지 검사
	Check(CD3D::Get()->GetDeviceContext()->Map(Input, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource));
	{
		memcpy(subResource.pData, InData, InputSize);
	}
	CD3D::Get()->GetDeviceContext()->Unmap(Input, 0);
}

void CRawBuffer::GetOutputData(void* OutData)
{
	CD3D::Get()->GetDeviceContext()->CopyResource(Result, Output);

	D3D11_MAPPED_SUBRESOURCE subResource;
	Check(CD3D::Get()->GetDeviceContext()->Map(Result, 0, D3D11_MAP_READ, 0, &subResource));
	{
		memcpy(OutData, subResource.pData, OutputSize);
	}
	CD3D::Get()->GetDeviceContext()->Unmap(Result, 0);
}
