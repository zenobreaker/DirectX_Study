#pragma once

class CCubeMap
{
public:
	CCubeMap(wstring InMaterialFile, wstring InMeshFile, wstring InTextureFile);
	~CCubeMap();

	void Tick();
	void Render();

	CTransform* GetTransform();

private:
	CShader* Shader;
	CMeshRender* Mesh;
	CTransform* Transform;

	ID3D11ShaderResourceView* SRV;
	ID3DX11EffectShaderResourceVariable* sSRV;
};