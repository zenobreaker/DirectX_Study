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