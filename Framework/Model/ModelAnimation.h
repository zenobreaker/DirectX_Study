#pragma once

class CModelAnimation
{
public:
	friend class CAnimRender;

private:
	CModelAnimation();
	~CModelAnimation();

public:
	struct FFrameVector
	{
		float Time;
		FVector Value;

		FFrameVector()
		{
			Time = 0.0f;
			Value = FVector();
		}

		FFrameVector(float InTime, const FVector& InValue)
		{
			Time = InTime;
			Value = InValue;
		}
	};

	struct FFrameQuat
	{
		float Time;
		FQuaternion Value;

		FFrameQuat()
		{
			Time = 0.0f;
			Value = FQuaternion();
		}

		FFrameQuat(float InTime, const FQuaternion& InValue)
		{
			Time = InTime;
			Value = InValue;
		}
	};

public:
	struct FKeyframe
	{
		CModelBone* Bone = nullptr;

		vector<FFrameVector> Positions;
		vector<FFrameQuat> Rotations;
		vector<FFrameVector> Scalings;
	};

private:
	string Name;

	float Duration;
	float TickersPerSeconds;

	vector<FKeyframe*> Keyframes;

private:
	struct FClipTransform
	{
		FMatrix** Transform;

		FClipTransform()
		{
			Transform = new FMatrix * [MAX_MODEL_KEYFRAMES];

			for (UINT i = 0; i < MAX_MODEL_KEYFRAMES; i++)
				Transform[i] = new FMatrix[MAX_MODEL_TRANSFORMS];
		}

		~FClipTransform()
		{
			for (UINT i = 0; i < MAX_MODEL_KEYFRAMES; i++)
				DeleteArray(Transform[i]);

			DeleteArray(Transform);
		}
	};

private:
	void CalcClipTransform(const vector<CModelBone*>& InBones);
	void DeleteClipTransform();

private:
	FClipTransform* ClipTransform = nullptr;
};