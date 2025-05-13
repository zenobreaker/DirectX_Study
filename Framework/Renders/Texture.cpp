#include "Framework.h"
#include "Texture.h"

using namespace DirectX;

CTexture::CTexture(wstring InFileName, bool bDefaultPath)
	: CTexture(nullptr, "", InFileName, bDefaultPath)
{
		
}

CTexture::CTexture(CShader* InShader, string InParamName, wstring InFileName, bool bDefaultPath)
	: Shader(InShader)
{
	FileName = InFileName;

	if(bDefaultPath)
		FileName = L"../../_Textures/" + InFileName;

	Metadata = GetMetaData(FileName);
	SRV = CreateSRV(FileName, Metadata);

	FileName = CPath::GetFileNameWithoutExtension(InFileName);
	
	
	if(Shader != nullptr)
		sSRV = Shader->AsSRV(InParamName);
}

CTexture::~CTexture()
{
	Release(SRV);
}

void CTexture::Render()
{
	CheckNull(Shader);

	sSRV->SetResource(SRV);
}

DirectX::TexMetadata CTexture::GetMetaData(wstring InFilePath)
{
	HRESULT hr;
	DirectX::TexMetadata metadata;

	wstring ext = CPath::GetExtension(InFilePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(InFilePath.c_str(), metadata);
		Check(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(InFilePath.c_str(), DDS_FLAGS_NONE, metadata);
		Check(hr);
	}
	else if (ext == L"hdr")
	{
		assert(false);
	}
	else
	{
		hr = GetMetadataFromWICFile(InFilePath.c_str(), WIC_FLAGS_NONE, metadata);
		Check(hr);
	}

	return metadata;
}

ID3D11ShaderResourceView* CTexture::CreateSRV(wstring InFilePath, DirectX::TexMetadata& InMetadata)
{
	HRESULT hr;

	ScratchImage image;

	wstring ext = CPath::GetExtension(InFilePath);
	if (ext == L"tga")
	{
		hr = LoadFromTGAFile(InFilePath.c_str(), &InMetadata, image);
		Check(hr);
	}
	else if (ext == L"dds")
	{
		hr = LoadFromDDSFile(InFilePath.c_str(), DDS_FLAGS_NONE, &InMetadata, image);
		Check(hr);
	}
	else if (ext == L"hdr")
	{
		assert(false);
	}
	else
	{
		hr = LoadFromWICFile(InFilePath.c_str(), WIC_FLAGS_NONE, &InMetadata, image);
		Check(hr);
	}


	ID3D11ShaderResourceView* srv = nullptr;

	hr = DirectX::CreateShaderResourceView(CD3D::Get()->GetDevice(), image.GetImages(), image.GetImageCount(), InMetadata, &srv);
	Check(hr);

	return srv;
}

D3D11_TEXTURE2D_DESC CTexture::ReadPixel(vector<FColor>& OutPixel)
{
	return ReadPixel(DXGI_FORMAT_UNKNOWN, OutPixel);
}

D3D11_TEXTURE2D_DESC CTexture::ReadPixel(DXGI_FORMAT InFormat, vector<FColor>& OutPixel)
{
	ID3D11Texture2D* texture;
	SRV->GetResource((ID3D11Resource**)&texture);

	if (InFormat == DXGI_FORMAT_UNKNOWN)
	{
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		InFormat = desc.Format;
	}

	return ReadPixel(texture, InFormat, OutPixel);
}

D3D11_TEXTURE2D_DESC CTexture::ReadPixel(ID3D11Texture2D* InSource, DXGI_FORMAT InFormat, vector<FColor>& OutPixel)
{
	D3D11_TEXTURE2D_DESC sourceDesc;
	InSource->GetDesc(&sourceDesc);


	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = sourceDesc.Width;
	desc.Height = sourceDesc.Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = InFormat;
	desc.SampleDesc = sourceDesc.SampleDesc;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	ID3D11Texture2D* texture;
	Check(CD3D::Get()->GetDevice()->CreateTexture2D(&desc, nullptr, &texture));
	Check(D3DX11LoadTextureFromTexture(CD3D::Get()->GetDeviceContext(), InSource, nullptr, texture));


	UINT* colors = new UINT[desc.Width * desc.Height];

	D3D11_MAPPED_SUBRESOURCE subResource;
	CD3D::Get()->GetDeviceContext()->Map(texture, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(UINT) * desc.Width * desc.Height);
	}
	CD3D::Get()->GetDeviceContext()->Unmap(texture, 0);


	for (UINT y = 0; y < desc.Height; y++)
	{
		for (UINT x = 0; x < desc.Width; x++)
		{
			UINT index = desc.Width * y + x;

			OutPixel.push_back(colors[index]);
		}
	}

	DeleteArray(colors);
	Release(texture);

	return desc;
}

///////////////////////////////////////////////////////////////////////////////

CTextureArray::CTextureArray(CShader* InShader, string InParamName, const vector<wstring>& InNames, bool bDefaultPath, UINT InWidth, UINT InHeight, UINT InMipLevels)
	: Shader(InShader)
{
	vector<wstring> names;

	for (UINT i = 0; i < InNames.size(); i++)
	{
		wstring name = InNames[i];

		if (bDefaultPath)
			name = L"../../_Textures/" + name;

		names.push_back(name);
	}


	vector<ID3D11Texture2D*> textures;
	textures = CreateTexture(names, InWidth, InHeight, InMipLevels);


	D3D11_TEXTURE2D_DESC textureDesc;
	textures[0]->GetDesc(&textureDesc);


	ID3D11Texture2D* textureArray;
	//Texture2DArray
	{
		D3D11_TEXTURE2D_DESC desc;
		desc.Width = textureDesc.Width;
		desc.Height = textureDesc.Height;
		desc.MipLevels = textureDesc.MipLevels;
		desc.ArraySize = names.size();
		desc.Format = textureDesc.Format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		Check(CD3D::Get()->GetDevice()->CreateTexture2D(&desc, NULL, &textureArray));
	}

	for (UINT i = 0; i < textures.size(); i++)
	{
		for (UINT level = 0; level < textureDesc.MipLevels; level++)
		{
			D3D11_MAPPED_SUBRESOURCE subResource;
			CD3D::Get()->GetDeviceContext()->Map(textures[i], level, D3D11_MAP_READ, 0, &subResource);
			{
				UINT dest = D3D11CalcSubresource(level, i, textureDesc.MipLevels);

				CD3D::Get()->GetDeviceContext()->UpdateSubresource(textureArray, dest, nullptr, subResource.pData, subResource.RowPitch, subResource.DepthPitch);
			}
			CD3D::Get()->GetDeviceContext()->Unmap(textures[i], level);
		}
	}


	//Create File textures[0] -> test.png
	//D3DX11SaveTextureToFile(D3D::Get()->GetDeviceContext(), textureArray, D3DX11_IFF_PNG, L"../Test.png");

	//SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		desc.Format = textureDesc.Format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = textureDesc.MipLevels;
		desc.Texture2DArray.ArraySize = names.size();

		Check(CD3D::Get()->GetDevice()->CreateShaderResourceView(textureArray, &desc, &SRV));
	}

	for (ID3D11Texture2D* texture : textures)
		Release(texture);

	Release(textureArray);

	sSRVs = Shader->AsSRV(InParamName);
}

CTextureArray::~CTextureArray()
{
	Release(SRV);
}

void CTextureArray::Render()
{
	sSRVs->SetResource(SRV);
}

vector<ID3D11Texture2D*> CTextureArray::CreateTexture(const vector<wstring>& InNames, UINT InWidth, UINT InHeight, UINT InMipLevels)
{
	vector<ID3D11Texture2D*> returnTextures;
	returnTextures.resize(InNames.size());

	for (UINT i = 0; i < returnTextures.size(); i++)
	{
		TexMetadata metaData = CTexture::GetMetaData(InNames[i]);


		HRESULT hr;
		ScratchImage image;

		wstring ext = CPath::GetExtension(InNames[i]);
		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(InNames[i].c_str(), &metaData, image);
			Check(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(InNames[i].c_str(), DDS_FLAGS_NONE, &metaData, image);
			Check(hr);
		}
		else if (ext == L"hdr")
		{
			assert(false);
		}
		else
		{
			hr = LoadFromWICFile(InNames[i].c_str(), WIC_FLAGS_NONE, &metaData, image);
			Check(hr);
		}


		ScratchImage resizedImage;
		hr = DirectX::Resize(image.GetImages(), image.GetImageCount(), image.GetMetadata(), InWidth, InHeight, TEX_FILTER_DEFAULT, resizedImage);
		Check(hr);


		if (InMipLevels > 1)
		{
			ScratchImage mipmapedImage;
			hr = DirectX::GenerateMipMaps(resizedImage.GetImages(), resizedImage.GetImageCount(), resizedImage.GetMetadata(), D3DX11_FILTER_NONE, InMipLevels, mipmapedImage);
			Check(hr);

			hr = DirectX::CreateTextureEx
			(
				CD3D::Get()->GetDevice()
				, mipmapedImage.GetImages()
				, mipmapedImage.GetImageCount()
				, mipmapedImage.GetMetadata()
				, D3D11_USAGE_STAGING
				, 0
				, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE
				, 0
				, false
				, (ID3D11Resource**)&returnTextures[i]
			);
			Check(hr);
		}
		else
		{
			hr = DirectX::CreateTextureEx
			(
				CD3D::Get()->GetDevice()
				, resizedImage.GetImages()
				, resizedImage.GetImageCount()
				, resizedImage.GetMetadata()
				, D3D11_USAGE_STAGING
				, 0
				, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE
				, 0
				, false
				, (ID3D11Resource**)&returnTextures[i]
			);
			Check(hr);
		}
	}//for(i)

	return returnTextures;
}
