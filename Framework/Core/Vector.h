#pragma once

class FMatrix;
class FQuaternion;
class FMath;

//////////////////////////////////////////////////////////////////////////
///@brief 3D º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
class FVector
{
public:
	FVector(void);
	FVector(float value);
	FVector(float x, float y, float z);

	operator float* ();
	operator const float* ();
	
	
	FVector operator -(void);

	bool operator ==(const FVector& value2) const;
	bool operator !=(const FVector& value2) const;

	FVector operator +(const FVector& value2) const;
	FVector operator -(const FVector& value2) const;
	FVector operator *(const FVector& value2) const;
	FVector operator *(const float& scaleFactor) const;
	FVector operator /(const FVector& value2) const;
	FVector operator /(const float& divider) const;

	void operator +=(const FVector& value2);
	void operator -=(const FVector& value2);
	void operator *=(const FVector& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FVector& value2);
	void operator /=(const float& divider);


	//////////////////////////////////////////////////////////////////////////
	///@brief floatÇüÀÇ *¿¬»ê Ã³¸®
	///@param scalefactor : °ª
	///@param value2 : º¤ÅÍ
	///@return °á°ú º¤ÅÍ
	//////////////////////////////////////////////////////////////////////////
	friend FVector operator *(const float scaleFactor, const FVector& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector Add(FVector value1, FVector value2);
	static FVector Divide(FVector value1, FVector value2);
	static FVector Divide(FVector value1, float value2);
	static FVector Multiply(FVector value1, FVector value2);
	static FVector Multiply(FVector value1, float scaleFactor);
	static FVector Subtract(FVector value1, FVector value2);

	static FVector Negative(FVector value);

	static FVector Barycentric(FVector value1, FVector value2, FVector value3, float amount1, float amount2);

	static float Distance(FVector value1, FVector value2);
	static float DistanceSquared(FVector value1, FVector value2);

	static float Dot(FVector value1, FVector value2);
	static FVector Normalize(FVector value);

	static FVector Cross(FVector vector1, FVector vector2);
	static FVector Reflect(FVector vector, FVector normal);

	static FVector Min(FVector value1, FVector value2);
	static FVector Max(FVector value1, FVector value2);
	static FVector Clamp(FVector value1, FVector min, FVector max);

	static FVector Lerp(FVector value1, FVector value2, float amount);
	static FVector SmoothStep(FVector value1, FVector value2, float amount);
	static FVector CatmullRom(FVector value1, FVector value2, FVector value3, FVector value4, float amount);
	static FVector Hermite(FVector value1, FVector tangent1, FVector value2, FVector tangent2, float amount);

	static FVector Transform(FVector position, FMatrix matrix);
	static FVector Transform(FVector value, FQuaternion rotation);
	static FVector TransformNormal(FVector normal, FMatrix matrix);
	static FVector TransformCoord(FVector position, FMatrix matrix);

public:
	const static FVector Zero;///< 0.0f, 0.0f, 0.0f
	const static FVector One;///< 1.0f, 1.0f, 1.0f

	const static FVector UnitX;///< 1.0f, 0.0f, 0.0f
	const static FVector UnitY;///< 0.0f, 1.0f, 0.0f
	const static FVector UnitZ;///< 0.0f, 0.0f, 1.0f

	const static FVector Up;///< 0.0f, 1.0f, 0.0f
	const static FVector Down;///< 0.0f, -1.0f, 0.0f
	const static FVector Right;///< 1.0f, 0.0f, 0.0f
	const static FVector Left;///< -1.0f, 0.0f, 0.0f
	const static FVector Forward;///< 0.0f, 0.0f, 1.0f
	const static FVector Backward;///< 0.0f, 0.0f, -1.0f

	union
	{
		struct
		{
			float X;///< X
			float Y;///< Y
			float Z;///< Z
		};

		float V[3];
	};
	
};