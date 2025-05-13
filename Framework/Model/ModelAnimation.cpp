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

			bones[b] = animation * parent;
			ClipTransform->Transform[f][b] = invGlobal * bones[b];
		}//for(b)
	}//for(f)
}

void CModelAnimation::DeleteClipTransform()
{
	Delete(ClipTransform);
}
