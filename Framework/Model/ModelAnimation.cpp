#include "Framework.h"
#include "ModelAnimation.h"

CModelAnimation::CModelAnimation()
{
}

CModelAnimation::~CModelAnimation()
{
	for (CModelAnimation::FKeyframe* data : Keyframes)
		Delete(data);
}


void CModelAnimation::CalcClipTransform(const vector<CModelBone*>& InBones)
{
	ClipTransform = new FClipTransform();

	map<string, FKeyframe*> keyframeNameTable;

	for (UINT i = 0; i < Keyframes.size(); i++)
	{
		if (Keyframes[i] == nullptr)
			continue;

		string name = Keyframes[i]->Bone->GetName();
		keyframeNameTable[name] = Keyframes[i];
	}

	FMatrix* bones = new FMatrix[MAX_MODEL_TRANSFORMS];

	for (UINT f = 0; f <= (UINT)Duration; f++)
	{
		for (UINT b = 0; b < InBones.size(); b++)
		{
			CModelBone* bone = InBones[b];

			// 본의 전역 트랜스폼을 역행렬로 변환하여 본의 로컬좌표로 되돌림
			FMatrix invGlobal = bone->GetTransform();
			invGlobal = FMatrix::Invert(invGlobal);

			FMatrix parent;

			if (bone->GetParentIndex() < 0)
				parent = FMatrix::Identity;
			else
				parent = bones[bone->GetParentIndex()];

			auto iter = keyframeNameTable.find(bone->GetName());

			FMatrix animation = FMatrix::Identity;
			if (iter != keyframeNameTable.end())
			{
				FKeyframe* data = iter->second;

				FVector position;
				if (data->Positions.size() - 1 >= f)
				{
					position = data->Positions[f].Value;
				}
				else
				{
					UINT last = data->Positions.size() - 1;
					position = data->Positions[last].Value;
				}

				FVector scale;
				if (data->Scalings.size() - 1 >= f)
				{
					scale = data->Scalings[f].Value;
				}
				else
				{
					UINT last = data->Scalings.size() - 1;
					scale = data->Scalings[last].Value;
				}

				FQuaternion rotation;
				if (data->Rotations.size() - 1 >= f)
				{
					rotation = data->Rotations[f].Value;
				}
				else
				{
					UINT last = data->Rotations.size() - 1;
					rotation = data->Rotations[last].Value;
				}

				FMatrix S = FMatrix::CreateScale(scale);
				FMatrix R = FMatrix::CreateFromQuaternion(rotation);
				FMatrix T = FMatrix::CreateTranslation(position);

				animation = S * R * T;
			}
			else
			{
				// 누락된 본 처리: 애니메이션 키프레임 없을 때,
				// 로컬 트랜스폼 = 본 글로벌 * 부모 글로벌 역행렬 
				//FMatrix parentGlobal;
				//if (bone->GetParentIndex() < 0)
				//	parentGlobal = FMatrix::Identity;
				//else
				//	parentGlobal = InBones[bone->GetParentIndex()]->GetTransform();

				//animation = bone->GetTransform() * FMatrix::Invert(parentGlobal);
				animation = bone->GetLocalBindTransform();
			}
			// 현재 본의 애니메이션 변환을 부모 본의 트랜스폼과 결합
			//bones[b] 현재 프레임의 글로벌 
			// animtion은 로컬 
			// parent는 부모의 글로벌
			bones[b] = animation * parent;
			// 본의 트랜스폼을 월드 좌표계에서 로컬좌표계로 변환 후 저장.
			ClipTransform->Transform[f][b] = invGlobal * bones[b];
		}//for(b)
	}//for(f)
}

void CModelAnimation::DeleteClipTransform()
{
	Delete(ClipTransform);
}
