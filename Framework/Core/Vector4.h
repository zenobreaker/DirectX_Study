#pragma once

class FVector2D;
class FVector;
class FMatrix;
class FQuaternion;

//////////////////////////////////////////////////////////////////////////
///@brief 4D º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
class FVector4
{
public:
	FVector4(void);
	FVector4(float x, float y, float z, float w);
	FVector4(FVector2D value, float z, float w);
	FVector4(FVector value, float w);
	FVector4(float value);

	
	operator float* ();
	operator const float* ();

	FVector4 operator -(void);

	bool operator ==(const FVector4& value2) const;
	bool operator !=(const FVector4& value2) const;

	FVector4 operator +(const FVector4& value2) const;
	FVector4 operator -(const FVector4& value2) const;
	FVector4 operator *(const FVector4& value2) const;
	FVector4 operator *(const float& scaleFactor) const;
	FVector4 operator /(const FVector4& value2) const;
	FVector4 operator /(const float& divider) const;

	void operator +=(const FVector4& value2);
	void operator -=(const FVector4& value2);
	void operator *=(const FVector4& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FVector4& value2);
	void operator /=(const float& divider);


	//////////////////////////////////////////////////////////////////////////
	///@brief floatÇüÀÇ *¿¬»ê Ã³¸®
	///@param scalefactor : °ª
	///@param value2 : º¤ÅÍ
	///@return °á°ú º¤ÅÍ
	//////////////////////////////////////////////////////////////////////////
	friend FVector4 operator *(const float scaleFactor, const FVector4& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector4 Add(FVector4 value1, FVector4 value2);
	static FVector4 Divide(FVector4 value1, FVector4 value2);
	static FVector4 Divide(FVector4 value1, float divider);
	static FVector4 Multiply(FVector4 value1, FVector4 value2);
	static FVector4 Multiply(FVector4 value1, float scaleFactor);
	static FVector4 Subtract(FVector4 value1, FVector4 value2);

	static FVector4 Negative(FVector4 value);


	static FVector4 Barycentric(FVector4 value1, FVector4 value2, FVector4 value3, float amount1, float amount2);

	static float Distance(FVector4 value1, FVector4 value2);
	static float DistanceSquared(FVector4 value1, FVector4 value2);

	static float Dot(FVector4 value1, FVector4 value2);
	static FVector4 Normalize(FVector4 value);

	static FVector4 Min(FVector4 value1, FVector4 value2);
	static FVector4 Max(FVector4 value1, FVector4 value2);
	static FVector4 Clamp(FVector4 value1, FVector4 min, FVector4 max);

	static FVector4 Lerp(FVector4 value1, FVector4 value2, float amount);
	static FVector4 SmoothStep(FVector4 value1, FVector4 value2, float amount);
	static FVector4 CatmullRom(FVector4 value1, FVector4 value2, FVector4 value3, FVector4 value4, float amount);
	static FVector4 Hermite(FVector4 value1, FVector4 tangent1, FVector4 value2, FVector4 tangent2, float amount);

	static FVector4 Transform(FVector2D position, FMatrix matrix);
	static FVector4 Transform(FVector position, FMatrix matrix);
	static FVector4 Transform(FVector4 position, FMatrix matrix);

	static FVector4 Transform(FVector2D value, FQuaternion rotation);
	static FVector4 Transform(FVector value, FQuaternion rotation);
	static FVector4 Transform(FVector4 value, FQuaternion rotation);

public:
	const static FVector4 Zero;///< 0.0f, 0.0f, 0.0f, 0.0f
	const static FVector4 One;///< 1.0f, 1.0f, 1.0f, 1.0f

	const static FVector4 UnitX;///< 1.0f, 0.0f, 0.0f, 0.0f
	const static FVector4 UnitY;///< 0.0f, 1.0f, 0.0f, 0.0f
	const static FVector4 UnitZ;///< 0.0f, 0.0f, 1.0f, 0.0f
	const static FVector4 UnitW;///< 0.0f, 0.0f, 1.0f, 1.0f

	union
	{
		struct
		{
			float X;///< X
			float Y;///< Y
			float Z;///< Z
			float W;///< W
		};

		float V[4];
	};
};