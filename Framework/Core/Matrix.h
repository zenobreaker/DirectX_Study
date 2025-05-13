#pragma once

class FVector;
class FQuaternion;
class FPlane;

//////////////////////////////////////////////////////////////////////////
///@brief 행렬
//////////////////////////////////////////////////////////////////////////
class FMatrix
{
public:
	FMatrix(void);
	FMatrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	FVector Up();			void Up(FVector value);
	FVector Down();			void Down(FVector value);
	FVector Right();		void Right(FVector value);
	FVector Left();			void Left(FVector value);
	FVector Forward();		void Forward(FVector value);
	FVector Backward();		void Backward(FVector value);
	FVector Translate();	void Translate(FVector value);


	operator float* ();
	operator const float* ();

	FMatrix operator -();

	bool operator ==(const FMatrix& matrix2) const;
	bool operator !=(const FMatrix& matrix2) const;

	FMatrix operator +(const FMatrix& matrix2) const;
	FMatrix operator -(const FMatrix& matrix2) const;
	FMatrix operator *(const FMatrix& matrix2) const;
	FMatrix operator *(const float& scaleFactor) const;
	FMatrix operator /(const FMatrix& matrix2) const;
	FMatrix operator /(const float& divider) const;

	void operator +=(const FMatrix& matrix2);
	void operator -=(const FMatrix& matrix2);
	void operator *=(const FMatrix& matrix2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FMatrix& matrix2);
	void operator /=(const float& divider);

	//////////////////////////////////////////////////////////////////////////
	///@brief float형의 *연산 처리
	///@param scalefactor : 값
	///@param matrix2 : 매트릭스
	///@return 결과 매트릭스
	//////////////////////////////////////////////////////////////////////////
	friend FMatrix operator *(const float scaleFactor, const FMatrix& matrix2)
	{
		return matrix2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::string ToStringRow1();
	std::string ToStringRow2();
	std::string ToStringRow3();
	std::string ToStringRow4();

	
	float Determinant();

	bool Decompose(FVector& scale, FQuaternion& rotation, FVector& translation);
	bool DecomposeUniformScale(float& scale, FQuaternion& rotation, FVector& translation);

	static FMatrix Add(FMatrix matrix1, FMatrix matrix2);
	static FMatrix Divide(FMatrix matrix1, FMatrix matrix2);
	static FMatrix Divide(FMatrix matrix1, float divider);
	static FMatrix Multiply(FMatrix matrix1, FMatrix matrix2);
	static FMatrix Multiply(FMatrix matrix1, float scaleFactor);

	static FMatrix Negative(FMatrix matrix);

	static FMatrix CreateBillboard(FVector objectPosition, FVector cameraPosition, FVector cameraUpVector, FVector* cameraForwardVector = NULL);

	static FMatrix CreateTranslation(FVector position);
	static FMatrix CreateTranslation(float xPosition, float yPosition, float zPosition);

	static FMatrix CreateScale(FVector scales);
	static FMatrix CreateScale(float xScale, float yScale, float zScale);
	static FMatrix CreateScale(float scale);

	static FMatrix CreateRotationX(float radians);
	static FMatrix CreateRotationY(float radians);
	static FMatrix CreateRotationZ(float radians);
	static FMatrix CreateFromAxisAngle(FVector axis, float angle);

	static FMatrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static FMatrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	static FMatrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);

	static FMatrix CreateLookAt(FVector cameraPosition, FVector cameraTarget, FVector cameraUpVector);
	static FMatrix CreateWorld(FVector position, FVector forward, FVector up);
	static FMatrix CreateFromQuaternion(FQuaternion quaternion);
	static FMatrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);

	static FMatrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static FMatrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

	static FMatrix Transform(FMatrix value, FQuaternion rotation);
	static FMatrix Transpose(FMatrix matrix);
	static FMatrix Invert(FMatrix matrix);
	static FMatrix Lerp(FMatrix matrix1, FMatrix matrix2, float amount);

private:
	struct CanonicalBasis
	{
		FVector Row0;
		FVector Row1;
		FVector Row2;
	};

	struct VectorBasis
	{
		class FVector* Element0;
		class FVector* Element1;
		class FVector* Element2;
	};

public:
	const static FMatrix Identity;

	union
	{
		struct
		{
			float M11; float M12; float M13; float M14;
			float M21; float M22; float M23; float M24;
			float M31; float M32; float M33; float M34;
			float M41; float M42; float M43; float M44;
		};

		float M[16];
	};
	
};