#pragma once

class CAnimRender : public CMeshRender 
{
public:
	CAnimRender(CShader* InShader);
	~CAnimRender();

	void Tick() override;
	void Render() override;

public:
	UINT GetAnimationCount() { return Animations.size(); }

public:
	void ReadAnimation(wstring InName);
	void Finish_ReadDatas();
	void ChangeClip(int InIndex, int InClipIndex, float TakeTime = 1.0f, float PlaySpeed = 1.0f);

private:
	void ReadAnimationData(wstring InName);
	void CreateClipTransforms();

private:
	vector<wstring> AnimationFiles;
	vector<CModelAnimation*> Animations;

private:
	ID3D11Texture2D* ClipTexture = nullptr;
	ID3D11ShaderResourceView* ClipSRV;
	ID3DX11EffectShaderResourceVariable* sClipSRV;

private:
	struct FAnimFrameDesc
	{
		int Clip = -1;

		float Duration;
		float TickersPerSeconds;
		float Padding;

		float PlaySpeed;
		float StartTime;

		float Padding2[2];
	};// AnimFrameData;

	struct FAnimBlendingDesc
	{
		float TakeTime = 1.0f;
		float ChangeStartTime;
		float Padding[2];

		FAnimFrameDesc Current;
		FAnimFrameDesc Next;
	} AnimBlendingData[MAX_INSTANCE_COUNT];

	CConstantBuffer* CBuffer;

	vector<UINT> ClipChanges;
};