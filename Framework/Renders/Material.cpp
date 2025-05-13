#include "Framework.h"
#include "Material.h"

CMaterial::CMaterial()
{
	
}

CMaterial::CMaterial(CShader* InShader)
	: Shader(InShader)
{
	CBuffer = new CConstantBuffer(Shader, "CB_Material", &Data, sizeof(FDesc));	
}

CMaterial::~CMaterial()
{
	Delete(CBuffer);

	Delete(DiffuseMap);
	Delete(SpecularMap);
	Delete(NormalMap);
}

void CMaterial::Render()
{
	CheckFalse(bDraw);
	CheckNull(Shader);


	CBuffer->Render();

	if (DiffuseMap != nullptr)
		DiffuseMap->Render();

	if (SpecularMap != nullptr)
		SpecularMap->Render();

	if (NormalMap != nullptr)
		NormalMap->Render();

	//Shader->SetTechniqueNumber(Technique);
	Shader->SetPassNumber(Pass);
}

void CMaterial::SetDiffuseMap(wstring InFilePath, bool bDefaultPath)
{
	DiffuseMap = new CTexture(Shader, "DiffuseMap", InFilePath, bDefaultPath);
}

void CMaterial::SetSpecularMap(wstring InFilePath, bool bDefaultPath)
{
	SpecularMap = new CTexture(Shader, "SpecularMap", InFilePath, bDefaultPath);
}

void CMaterial::SetNormalMap(wstring InFilePath, bool bDefaultPath)
{
	NormalMap = new CTexture(Shader, "NormalMap", InFilePath, bDefaultPath);
}
