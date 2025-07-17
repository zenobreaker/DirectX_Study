#pragma once

#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
private:
	const float WindowWidth = 400.0f;

public:
	void Initialize();
	void Destroy();
	void Tick();
	void Render();

private:
	void OnGUI();
	void OnGUI_List(); 
	void OnGUI_Settings();
	void OnGUI_WriteFile(); 

private:
	vector<wstring> ParticleFileList;

private:
	void ReadTextureFile(wstring InFileName);
	void SaveParticleData(wstring InFileName);

	wstring SaveParticleFile(wstring InFileName, FParticleData& InData);

private:
	void UpdateParticleFileList();

private:
	void CreateFloor(); 

private:
	CShader* Shader; 
	CMeshRender* Floor = nullptr;

private:
	ImVec2 ButtonSize;
	wstring CurrentFile;

	bool bLoop = false;
	UINT MaxParticles = 0;

	CParticle* Particle = nullptr;
};