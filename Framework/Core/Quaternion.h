#pragma once

class FVector;
class FMatrix;

//////////////////////////////////////////////////////////////////////////
///@brief 사원수
//////////////////////////////////////////////////////////////////////////
class FQuaternion
{
public:
	FQuaternion(void);
	FQuaternion(float x, float y, float z, float w);
	FQuaternion(FVector vectorPart, float scalarPart);


	operator float* ();
	operator const float* ();

	FQuaternion operator -(void);

	bool operator ==(const FQuaternion& quaternion2) const;
	bool operator !=(const FQuaternion& quaternion2) const;

	FQuaternion operator +(const FQuaternion& quaternion2) const;
	FQuaternion operator -(const FQuaternion& quaternion2) const;
	FQuaternion operator *(const FQuaternion& quaternion2) const;
	FQuaternion operator *(const float& scaleFactor) const;
	FQuaternion operator /(const FQuaternion& quaternion2) const;

	void operator +=(const FQuaternion& quaternion2);
	void operator -=(const FQuaternion& quaternion2);
	void operator *=(const FQuaternion& quaternion2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FQuaternion& quaternion2);


	//////////////////////////////////////////////////////////////////////////
	///@brief float형의 *연산 처리
	///@param scalefactor : 값
	///@param value2 : 벡터
	///@return 결과 벡터
	//////////////////////////////////////////////////////////////////////////
	friend FQuaternion operator *(const float scaleFactor, const FQuaternion& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();
	static FQuaternion Normalize(FQuaternion quaternion);

	void Conjugate();
	static FQuaternion Conjugate(FQuaternion value);
	static FQuaternion Inverse(FQuaternion quaternion);

	static FQuaternion Add(FQuaternion quaternion1, FQuaternion quaternion2);
	static FQuaternion Divide(FQuaternion quaternion1, FQuaternion quaternion2);
	static FQuaternion Multiply(FQuaternion quaternion1, FQuaternion quaternion2);
	static FQuaternion Multiply(FQuaternion quaternion1, float scaleFactor);
	static FQuaternion Subtract(FQuaternion quaternion1, FQuaternion quaternion2);

	static FQuaternion Negative(FQuaternion quaternion);

	static FQuaternion CreateFromAxisAngle(FVector axis, float angle);
	static FQuaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static FQuaternion CreateFromRotationMatrix(FMatrix matrix);

	static float Dot(FQuaternion quaternion1, FQuaternion quaternion2);

	static FQuaternion Slerp(FQuaternion quaternion1, FQuaternion quaternion2, float amount);
	static FQuaternion Lerp(FQuaternion quaternion1, FQuaternion quaternion2, float amount);

	static FQuaternion Concatenate(FQuaternion quaternion1, FQuaternion quaternion2);

public:
	const static FQuaternion Identity;///< 0.0f, 0.0f, 0.0f, 1.0f

	union
	{
		struct
		{
			float X;///< X
			float Y;///< Y
			float Z;///< Z
			float W;///< W
		};

		float Q[4];
	};
};