#include "Framework.h"
#include "CubeMap.h"

CCubeMap::CCubeMap(wstring InMaterialFile, wstring InMeshFile, wstring InTextureFile)
{
	Shader = CShaders::Get()->GetShader(L"00_CubeMap.fxo");
	

	Mesh = new CMeshRender(Shader);
	Mesh->ReadMaterial(InMaterialFile);
	Mesh->ReadMesh(InMeshFile);

	Transform = Mesh->AddTransform();

	
	InTextureFile = L"../../_Textures/" + InTextureFile;

	Check(D3DX11CreateShaderResourceViewFromFile
	(
		CD3D::Get()->GetDevice(), InTextureFile.c_str(), nullptr, nullptr, &SRV, nullptr
	));

	sSRV = Shader->AsSRV("CubeMap");
}

CCubeMap::~CCubeMap()
{
	Delete(Mesh);

	Release(SRV);
}

void CCubeMap::Tick()
{
	Mesh->Tick();
}

void CCubeMap::Render()
{
	sSRV->SetResource(SRV);
	Mesh->Render();
}

CTransform* CCubeMap::GetTransform()
{
	return Transform;
}
