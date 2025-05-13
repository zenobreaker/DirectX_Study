#include "Framework.h"
#include "AnimRender.h"

CAnimRender::CAnimRender(CShader* InShader)
	: CMeshRender(InShader)
{
	sClipSRV = Shader->AsSRV("AnimationClipMaps");
	
	CBuffer = new CConstantBuffer(Shader, "CB_AnimBlendingData", &AnimBlendingData, sizeof(FAnimBlendingDesc) * MAX_INSTANCE_COUNT);
}

CAnimRender::~CAnimRender()
{
	for (CModelAnimation* animation : Animations)
		Delete(animation);

	Release(ClipTexture);
	Release(ClipSRV);

	Delete(CBuffer);
}

void CAnimRender::Tick()
{
	for (int i = (int)ClipChanges.size() - 1; i >= 0; i--)
	{
		UINT index = ClipChanges[i];

		if (AnimBlendingData[index].Next.Clip > -1)
		{
			float running = CTimer::Get()->GetRunningTime();
			float current = AnimBlendingData[index].ChangeStartTime;
			float take = AnimBlendingData[index].TakeTime;

			float time = (running - current) / take;

			if (time >= 1.0f)
			{
				AnimBlendingData[index].ChangeStartTime = 0.0f;
				AnimBlendingData[index].TakeTime = 0.0f;

				AnimBlendingData[index].Current = AnimBlendingData[index].Next;

				AnimBlendingData[index].Next.Clip = -1;

				ClipChanges.erase(ClipChanges.begin() + i);
			}
		}
	}//for(i)	

	Super::Tick();
}

void CAnimRender::Render()
{
	CBuffer->Render();
	sClipSRV->SetResource(ClipSRV);

	Super::Render();
}

void CAnimRender::ReadAnimation(wstring InName)
{
	InName = L"../../_Models/" + InName + L".animation";

	AnimationFiles.push_back(InName);
}

void CAnimRender::ReadAnimationData(wstring InName)
{
	CBinaryReader* reader = new CBinaryReader();
	reader->Open(InName);


	CModelAnimation* animation = new CModelAnimation();

	animation->Name = reader->FromString();
	animation->Duration = reader->FromFloat();
	animation->TickersPerSeconds = reader->FromFloat();

	UINT count = reader->FromUInt();
	animation->Keyframes.assign(count, nullptr);

	for (UINT i = 0; i < count; i++)
	{
		CModelAnimation::FKeyframe* data = new CModelAnimation::FKeyframe();

		string name = reader->FromString();
		for (CModelBone* bone : Bones)
		{
			if (bone->Name == name)
			{
				data->Bone = bone;

				break;
			}
		}

		
		UINT frameCount = 0;

		frameCount = reader->FromUInt();
		CModelAnimation::FFrameVector* position = new CModelAnimation::FFrameVector[frameCount];
		reader->FromByte((void**)&position, sizeof(CModelAnimation::FFrameVector) * frameCount);
		data->Positions.assign(position, position + frameCount);

		frameCount = reader->FromUInt();
		CModelAnimation::FFrameVector* scaling = new CModelAnimation::FFrameVector[frameCount];
		reader->FromByte((void**)&scaling, sizeof(CModelAnimation::FFrameVector) * frameCount);
		data->Scalings.assign(scaling, scaling + frameCount);

		frameCount = reader->FromUInt();
		CModelAnimation::FFrameQuat* rotation = new CModelAnimation::FFrameQuat[frameCount];
		reader->FromByte((void**)&rotation, sizeof(CModelAnimation::FFrameQuat) * frameCount);
		data->Rotations.assign(rotation, rotation + frameCount);


		if (data->Bone == nullptr)
		{
			Delete(data);
			animation->Keyframes[i] = nullptr;

			continue;
		}
		
		animation->Keyframes[i] = data;			
	}

	reader->Close();
	Delete(reader);


	animation->CalcClipTransform(Bones);

	Animations.push_back(animation);
}

void CAnimRender::Finish_ReadDatas()
{
	for (const wstring& name : AnimationFiles)
		ReadAnimationData(name);

	CreateClipTransforms();
	
	for(UINT i = 0; i < MAX_INSTANCE_COUNT; i++)
		ChangeClip(i, -1);
}

void CAnimRender::CreateClipTransforms()
{
	//Create Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4; //Bone
		desc.Height = MAX_MODEL_KEYFRAMES; //Frame
		desc.ArraySize = Animations.size(); //Clip
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //16Byte * 4 = 64 Byte
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;


		UINT pageSize = MAX_MODEL_TRANSFORMS * 4 * 16 * MAX_MODEL_KEYFRAMES;
		void* p = VirtualAlloc(nullptr, pageSize * Animations.size(), MEM_RESERVE, PAGE_READWRITE);

		//MEMORY_BASIC_INFORMATION infomation;
		//ULONG size = VirtualQuery(p, &infomation, sizeof(MEMORY_BASIC_INFORMATION));

		for (UINT c = 0; c < Animations.size(); c++)
		{
			UINT start = c * pageSize;

			for (UINT f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* temp = (BYTE*)p + MAX_MODEL_TRANSFORMS * f * sizeof(FMatrix) + start;

				VirtualAlloc(temp, MAX_MODEL_TRANSFORMS * sizeof(FMatrix), MEM_COMMIT, PAGE_READWRITE);

				void* source = Animations[c]->ClipTransform->Transform[f];
				memcpy(temp, source, MAX_MODEL_TRANSFORMS * sizeof(FMatrix));
			}
		}//for(c)


		//SSD -> VRAM
		{
			D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[Animations.size()];
			for (UINT c = 0; c < Animations.size(); c++)
			{
				void* temp = (BYTE*)p + c * pageSize;

				subResource[c].pSysMem = temp;
				subResource[c].SysMemPitch = MAX_MODEL_TRANSFORMS * sizeof(FMatrix);
				subResource[c].SysMemSlicePitch = pageSize;
			}
			Check(CD3D::Get()->GetDevice()->CreateTexture2D(&desc, subResource, &ClipTexture));

			DeleteArray(subResource);
		}

		//Clear
		{
			for (CModelAnimation* animation : Animations)
				animation->DeleteClipTransform();

			VirtualFree(p, 0, MEM_RELEASE);
		}

		//Create SRV
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MipLevels = 1;
			desc.Texture2DArray.ArraySize = Animations.size();

			Check(CD3D::Get()->GetDevice()->CreateShaderResourceView(ClipTexture, &desc, &ClipSRV));
		}
	}
}

void CAnimRender::ChangeClip(int InIndex, int InClipIndex, float TakeTime, float PlaySpeed)
{
	if (InClipIndex < 0) //최초 실행
	{
		AnimBlendingData[InIndex].Current.Clip = 0;

		AnimBlendingData[InIndex].Current.Duration = Animations[0]->Duration + 1.0f;
		AnimBlendingData[InIndex].Current.TickersPerSeconds = Animations[0]->TickersPerSeconds;

		AnimBlendingData[InIndex].Current.PlaySpeed = 1.0f;
		AnimBlendingData[InIndex].Current.StartTime = CTimer::Get()->GetRunningTime();

		return;
	}

	CheckTrue(AnimBlendingData[InIndex].Current.Clip == InClipIndex);


	AnimBlendingData[InIndex].ChangeStartTime = CTimer::Get()->GetRunningTime();
	AnimBlendingData[InIndex].TakeTime = TakeTime;


	AnimBlendingData[InIndex].Next.Clip = InClipIndex;

	AnimBlendingData[InIndex].Next.Duration = Animations[InClipIndex]->Duration + 1.0f;
	AnimBlendingData[InIndex].Next.TickersPerSeconds = Animations[InClipIndex]->TickersPerSeconds;

	AnimBlendingData[InIndex].Next.PlaySpeed = PlaySpeed;
	AnimBlendingData[InIndex].Next.StartTime = CTimer::Get()->GetRunningTime();

	ClipChanges.push_back(InIndex);
}