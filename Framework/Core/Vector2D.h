#pragma once

class FMatrix;
class FQuaternion;

//////////////////////////////////////////////////////////////////////////
///@brief 2D º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
class FVector2D
{
public:
	FVector2D(void);
	FVector2D(float value);
	FVector2D(float x, float y);

	operator float* ();
	operator const float* ();

	FVector2D operator -(void);

	bool operator ==(const FVector2D& value2) const;
	bool operator !=(const FVector2D& value2) const;

	FVector2D operator +(const FVector2D& value2) const;
	FVector2D operator -(const FVector2D& value2) const;
	FVector2D operator *(const FVector2D& value2) const;
	FVector2D operator *(const float& scaleFactor) const;
	FVector2D operator /(const FVector2D& value2) const;
	FVector2D operator /(const float& divider) const;

	void operator +=(const FVector2D& value2);
	void operator -=(const FVector2D& value2);
	void operator *=(const FVector2D& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FVector2D& value2);
	void operator /=(const float& divider);


	//////////////////////////////////////////////////////////////////////////
	///@brief floatÇüÀÇ *¿¬»ê Ã³¸®
	///@param scalefactor : °ª
	///@param value2 : º¤ÅÍ
	///@return °á°ú º¤ÅÍ
	//////////////////////////////////////////////////////////////////////////
	friend FVector2D operator *(const float scaleFactor, const FVector2D& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector2D Add(FVector2D value1, FVector2D value2);
	static FVector2D Divide(FVector2D value1, FVector2D value2);
	static FVector2D Divide(FVector2D value1, float divider);
	static FVector2D Multiply(FVector2D value1, FVector2D value2);
	static FVector2D Multiply(FVector2D value1, float scaleFactor);
	static FVector2D Subtract(FVector2D value1, FVector2D value2);

	static FVector2D Negative(FVector2D value);

	static FVector2D Barycentric(FVector2D value1, FVector2D value2, FVector2D value3, float amount1, float amount2);

	static float Distance(FVector2D value1, FVector2D value2);
	static float DistanceSquared(FVector2D value1, FVector2D value2);

	static float Dot(FVector2D value1, FVector2D value2);
	static FVector2D Normalize(FVector2D value);

	static FVector2D Reflect(FVector2D vector, FVector2D normal);

	static FVector2D Min(FVector2D value1, FVector2D value2);
	static FVector2D Max(FVector2D value1, FVector2D value2);
	static FVector2D Clamp(FVector2D value1, FVector2D min, FVector2D max);

	static FVector2D Lerp(FVector2D value1, FVector2D value2, float amount);
	static FVector2D SmoothStep(FVector2D value1, FVector2D value2, float amount);
	static FVector2D CatmullRom(FVector2D value1, FVector2D value2, FVector2D value3, FVector2D value4, float amount);
	static FVector2D Hermite(FVector2D value1, FVector2D tangent1, FVector2D value2, FVector2D tangent2, float amount);

	static FVector2D Transform(FVector2D position, FMatrix matrix);
	static FVector2D Transform(FVector2D value, FQuaternion rotation);
	static FVector2D TransformNormal(FVector2D normal, FMatrix matrix);

public:
	const static FVector2D Zero;///< 0.0f, 0.0f
	const static FVector2D One;///< 1.0f, 1.0f

	const static FVector2D UnitX;///< 1.0f, 0.0f
	const static FVector2D UnitY;///< 0.0f, 1.0f

	union
	{
		struct
		{
			float X;///< X
			float Y;///< Y
		};

		float V[2];
	};
};