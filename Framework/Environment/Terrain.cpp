#include "Framework.h"
#include "Terrain.h"

CTerrain::CTerrain(wstring InHeightMapFileName, wstring InShader, float InMaxHeight)
	: CRenderer(InShader), HeightFileName(InHeightMapFileName), HeightScale(InMaxHeight)
{
	HeightMap = new CTexture(HeightFileName);

	Regeneration();
	CBuffer = new CConstantBuffer(Shader, "CB_Terrain", &Data, sizeof(FDesc));
}

CTerrain::~CTerrain()
{
	Delete(HeightMap);

	DeleteArray(Vertices);
	DeleteArray(Indices);

	Delete(CBuffer);

	Delete(Textures);
	Delete(NormalTextures);
}

void CTerrain::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Terrain");
	ImGui::InputFloat("TilingX Terrain", &Data.Tiling.X, 1.0f);
	ImGui::InputFloat("TilingY Terrain", &Data.Tiling.Y, 1.0f);

	ImGui::InputFloat("LowRatio Terrain", &HeightLowRatio, 0.1f);
	HeightLowRatio = FMath::Clamp<float>(HeightLowRatio, 0.0f, 1.0f);

	ImGui::InputFloat("HighRatio Terrain", &HeightHighRatio, 0.1f);
	HeightHighRatio = FMath::Clamp<float>(HeightHighRatio, 0.0f, 1.0f);

	ImGui::InputFloat("GentleAngle Terrain", &HeightGentleAngle, 1.0f);
	HeightGentleAngle = FMath::Clamp<float>(HeightGentleAngle, 1.0f, 89.0f);

	ImGui::InputFloat("SteepAngle Terrain", &HeightSteepAngle, 1.0f);
	HeightSteepAngle = FMath::Clamp<float>(HeightSteepAngle, 1.0f, 89.0f);

	if (ImGui::Button("Regeneration Terrain"))
		Regeneration();

	ImGui::Separator();
	ImGui::ColorEdit3("Specular Terrain", Data.Specular);
	ImGui::InputFloat("Shininess Terrain", &Data.Specular.A, 0.01f);


	if (Textures == nullptr)
	{
		std::vector<wstring> files(TextureFiles, TextureFiles + 4);
		Textures = new CTextureArray(Shader, "TerrainMaps", files);
	}

	if (NormalTextures == nullptr)
	{
		std::vector<wstring> files(NormalFiles, NormalFiles + 4);
		NormalTextures = new CTextureArray(Shader, "TerrainNormalMaps", files);
	}

	Super::Tick();
}

void CTerrain::Render()
{
	Super::Render();

	CBuffer->Render();

	if (Textures != nullptr)
		Textures->Render();

	if (NormalTextures != nullptr)
		NormalTextures->Render();

	
	IA_TRIANGLELIST();

	Shader->SetPassNumber(4);
	Shader->DrawIndexed(ICount);
}



float CTerrain::GetY(UINT x, UINT z)
{
	return Vertices[Width * z + x].Position.Y;
}

const FVector4& CTerrain::GetWeights(UINT x, UINT z)
{
	return Vertices[Width * z + x].Weights;
}

void CTerrain::Regeneration()
{
	DeleteArray(Vertices);
	DeleteArray(Indices);

	Delete(VBuffer);
	Delete(IBuffer);


	CreateVertexData();
	CreateIndexData();
	CreateNormalAndTangentData();
	CreateWeightData();

	VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTerrain));
	IBuffer = new CIndexBuffer(Indices, ICount);
}

void CTerrain::SetBaseMap(wstring InFile, wstring InNormalFile)
{
	TextureFiles[0] = InFile;
	NormalFiles[0] = InNormalFile;
}

void CTerrain::SetLowMap(wstring InFile, wstring InNormalFile)
{
	TextureFiles[1] = InFile;
	NormalFiles[1] = InNormalFile;
}

void CTerrain::SetHighMap(wstring InFile, wstring InNormalFile)
{
	TextureFiles[2] = InFile;
	NormalFiles[2] = InNormalFile;
}

void CTerrain::SetSlopeMap(wstring InFile, wstring InNormalFile)
{
	TextureFiles[3] = InFile;
	NormalFiles[3] = InNormalFile;
}

void CTerrain::CreateVertexData()
{
	vector<FColor> pixels;
	HeightMap->ReadPixel(pixels);


	Width = HeightMap->GetWidth();
	Height = HeightMap->GetHeight();

	VCount = Width * Height;
	Vertices = new FVertexTerrain[VCount];
	for (UINT z = 0; z < Height; z++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			UINT index = Width * z + x;
			UINT pixel = Width * (Height - 1 - z) + x;

			Vertices[index].Position.X = (float)x;
			Vertices[index].Position.Y = pixels[pixel].R * HeightScale;
			Vertices[index].Position.Z = (float)z;

			Vertices[index].Uv.X = (float)x / (float)(Width - 1);
			Vertices[index].Uv.Y = 1.0f - ((float)z / (float)(Height - 1));
		}
	} //for(z)
}

void CTerrain::CreateIndexData()
{
	ICount = (Width - 1) * (Height - 1) * 6;
	Indices = new UINT[ICount];

	UINT index = 0;
	for (UINT z = 0; z < Height - 1; z++)
	{
		for (UINT x = 0; x < Width - 1; x++)
		{
			Indices[index + 0] = Width * z + x;
			Indices[index + 1] = Width * (z + 1) + x;
			Indices[index + 2] = Width * z + x + 1;

			Indices[index + 3] = Width * z + x + 1;
			Indices[index + 4] = Width * (z + 1) + x;
			Indices[index + 5] = Width * (z + 1) + x + 1;

			index += 6;
		}
	}
}

void CTerrain::CreateNormalAndTangentData()
{
	for (UINT i = 0; i < ICount / 3; i++)
	{
		UINT index0 = Indices[i * 3 + 0];
		UINT index1 = Indices[i * 3 + 1];
		UINT index2 = Indices[i * 3 + 2];

		FVertexTerrain& v0 = Vertices[index0];
		FVertexTerrain& v1 = Vertices[index1];
		FVertexTerrain& v2 = Vertices[index2];

		FVector e1 = v1.Position - v0.Position;
		FVector e2 = v2.Position - v0.Position;

		//Normal Vector
		{
			FVector normal = FVector::Cross(e1, e2);

			v0.Normal += normal;
			v1.Normal += normal;
			v2.Normal += normal;
		}

		//Tangent Vector
		{
			FVector2D uv0 = Vertices[index0].Uv;
			FVector2D uv1 = Vertices[index1].Uv;
			FVector2D uv2 = Vertices[index2].Uv;

			float du1 = uv1.X - uv0.X;
			float du2 = uv2.X - uv0.X;
			float dv1 = uv1.Y - uv0.Y;
			float dv2 = uv2.Y - uv0.Y;

			float f = 1.0f / (du1 * dv2 - du2 * dv1);

			FVector tangent;
			tangent.X = f * (dv2 * e1.X - dv1 * e2.X);
			tangent.Y = f * (dv2 * e1.Y - dv1 * e2.Y);
			tangent.Z = f * (dv2 * e1.Z - dv1 * e2.Z);

			v0.Tangent += tangent;
			v1.Tangent += tangent;
			v2.Tangent += tangent;
		}
	}

	for (UINT i = 0; i < VCount; i++)
	{
		Vertices[i].Normal = FVector::Normalize(Vertices[i].Normal);
		Vertices[i].Tangent = FVector::Normalize(Vertices[i].Tangent);
	}
		
}

void CTerrain::CreateWeightData()
{
	for (UINT z = 0; z < Height; z++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			UINT index = Width * z + x;

			float scale = HeightScale;
			float low = HeightLowRatio * scale;
			float high = HeightHighRatio * scale;

			float y = Vertices[index].Position.Y;


			FVector normal = FVector(Vertices[index].Normal.X, 0.0f, Vertices[index].Normal.Z);
			float dot = FVector::Dot(Vertices[index].Normal, normal);
			float angle = FMath::ToDegrees(acosf(dot));

			FVector4 weights = FVector4::Zero;
			if (y < low) //가장 낮은
			{
				weights.Y = y / low;
				weights.X = 1.0f - weights.Y;
			}
			else if (y < high) //중간
			{
				weights.Z = (y - low) / (high - low);
				weights.Y = 1.0f - weights.Z;
			}
			else //가장 높은
			{
				weights.W = (y - high) / (scale - high) * (90.0f - angle) / 90.0f;
				weights.Z = 1.0f - weights.W;
			}

			if (angle < HeightGentleAngle)
			{
				float value = FMath::Clamp((90.0f - angle) / 90.0f, 0.0f, 1.0f);
				weights *= (1.0f - value);
				weights.W += value;
			}

			if (angle > HeightSteepAngle && y > low)
			{
				weights *= 0.4f;
				weights.Z += 0.6f;
			}

			Vertices[index].Weights = weights;
		}//for(x)
	}//for(z)
}
