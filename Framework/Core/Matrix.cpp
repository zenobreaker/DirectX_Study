#include "Framework.h"
#include "Matrix.h"

//////////////////////////////////////////////////////////////////////////

const FMatrix FMatrix::Identity = FMatrix
(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f
);

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
FMatrix::FMatrix(void)
{
	M11 = 0.0f; M12 = 0.0f; M13 = 0.0f; M14 = 0.0f;
	M21 = 0.0f; M22 = 0.0f; M23 = 0.0f; M24 = 0.0f;
	M31 = 0.0f; M32 = 0.0f; M33 = 0.0f; M34 = 0.0f;
	M41 = 0.0f; M42 = 0.0f; M43 = 0.0f; M44 = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param m11 : M11
///@param m12 : M12
///@param m13 : M13
///@param m14 : M14
///@param m21 : M21
///@param m22 : M22
///@param m23 : M23
///@param m24 : M24
///@param m31 : M31
///@param m32 : M32
///@param m33 : M33
///@param m34 : M34
///@param m41 : M41
///@param m42 : M42
///@param m43 : M43
///@param m44 : M44
//////////////////////////////////////////////////////////////////////////
FMatrix::FMatrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	M11 = m11; M12 = m12; M13 = m13; M14 = m14;
	M21 = m21; M22 = m22; M23 = m23; M24 = m24;
	M31 = m31; M32 = m32; M33 = m33; M34 = m34;
	M41 = m41; M42 = m42; M43 = m43; M44 = m44;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Up()
{
	FVector vector;
	vector.X = M21; vector.Y = M22; vector.Z = M23;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Up(FVector value)
{
	M21 = value.X; M22 = value.Y; M23 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ� ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Down()
{
	FVector vector;
	vector.X = -M21; vector.Y = -M22; vector.Z = -M23;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ� ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Down(FVector value)
{
	M21 = -value.X; M22 = -value.Y; M23 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Right()
{
	FVector vector;
	vector.X = M11; vector.Y = M12; vector.Z = M13;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ� ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Right(FVector value)
{
	M11 = value.X; M12 = value.Y; M13 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Left()
{
	FVector vector;
	vector.X = -M11; vector.Y = -M12; vector.Z = -M13;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Left(FVector value)
{
	M11 = -value.X; M12 = -value.Y; M13 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������ ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Forward()
{
	FVector vector;
	vector.X = -M31; vector.Y = -M32; vector.Z = -M33;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������ ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Forward(FVector value)
{
	M31 = -value.X; M32 = -value.Y; M33 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����� ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Backward()
{
	FVector vector;
	vector.X = M31; vector.Y = M32; vector.Z = M33;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����� ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Backward(FVector value)
{
	M31 = value.X; M32 = value.Y; M33 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �̵� ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
FVector FMatrix::Translate()
{
	FVector vector;
	vector.X = M41; vector.Y = M42; vector.Z = M43;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �̵� ����
///@param value : ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::Translate(FVector value)
{
	M41 = value.X; M42 = value.Y; M43 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief float*
///@return ��� ������
//////////////////////////////////////////////////////////////////////////
FMatrix::operator float* ()
{
	return M;
}

FMatrix::operator const float* ()
{
	return M;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator-()
{
	FMatrix matrix;
	matrix.M11 = -M11; matrix.M12 = -M12; matrix.M13 = -M13; matrix.M14 = -M14;
	matrix.M21 = -M21; matrix.M22 = -M22; matrix.M23 = -M23; matrix.M24 = -M24;
	matrix.M31 = -M31; matrix.M32 = -M32; matrix.M33 = -M33; matrix.M34 = -M34;
	matrix.M41 = -M41; matrix.M42 = -M42; matrix.M43 = -M43; matrix.M44 = -M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param matrix2 : ��Ʈ����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool FMatrix::operator==(const FMatrix& matrix2) const
{
	if (M11 == matrix2.M11 && M22 == matrix2.M22 && (M33 == matrix2.M33 && M44 == matrix2.M44) && (M12 == matrix2.M12 && M13 == matrix2.M13 && (M14 == matrix2.M14 && M21 == matrix2.M21)) && (M23 == matrix2.M23 && M24 == matrix2.M24 && (M31 == matrix2.M31 && M32 == matrix2.M32) && (M34 == matrix2.M34 && M41 == matrix2.M41 && M42 == matrix2.M42)))
		return M43 == matrix2.M43;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param matrix2 : ��Ʈ����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool FMatrix::operator!=(const FMatrix& matrix2) const
{
	if (M11 == matrix2.M11 && M12 == matrix2.M12 && (M13 == matrix2.M13 && M14 == matrix2.M14) && (M21 == matrix2.M21 && M22 == matrix2.M22 && (M23 == matrix2.M23 && M24 == matrix2.M24)) && (M31 == matrix2.M31 && M32 == matrix2.M32 && (M33 == matrix2.M33 && M34 == matrix2.M34) && (M41 == matrix2.M41 && M42 == matrix2.M42 && M43 == matrix2.M43)))
		return M44 != matrix2.M44;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator+(const FMatrix& matrix2) const
{
	FMatrix matrix;
	matrix.M11 = M11 + matrix2.M11; matrix.M12 = M12 + matrix2.M12; matrix.M13 = M13 + matrix2.M13; matrix.M14 = M14 + matrix2.M14;
	matrix.M21 = M21 + matrix2.M21; matrix.M22 = M22 + matrix2.M22; matrix.M23 = M23 + matrix2.M23; matrix.M24 = M24 + matrix2.M24;
	matrix.M31 = M31 + matrix2.M31; matrix.M32 = M32 + matrix2.M32; matrix.M33 = M33 + matrix2.M33; matrix.M34 = M34 + matrix2.M34;
	matrix.M41 = M41 + matrix2.M41; matrix.M42 = M42 + matrix2.M42; matrix.M43 = M43 + matrix2.M43; matrix.M44 = M44 + matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator-(const FMatrix& matrix2) const
{
	FMatrix matrix;
	matrix.M11 = M11 - matrix2.M11; matrix.M12 = M12 - matrix2.M12; matrix.M13 = M13 - matrix2.M13; matrix.M14 = M14 - matrix2.M14;
	matrix.M21 = M21 - matrix2.M21; matrix.M22 = M22 - matrix2.M22; matrix.M23 = M23 - matrix2.M23; matrix.M24 = M24 - matrix2.M24;
	matrix.M31 = M31 - matrix2.M31; matrix.M32 = M32 - matrix2.M32; matrix.M33 = M33 - matrix2.M33; matrix.M34 = M34 - matrix2.M34;
	matrix.M41 = M41 - matrix2.M41; matrix.M42 = M42 - matrix2.M42; matrix.M43 = M43 - matrix2.M43; matrix.M44 = M44 - matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator*(const FMatrix& matrix2) const
{
	FMatrix matrix;
	matrix.M11 = (M11 * matrix2.M11 + M12 * matrix2.M21 + M13 * matrix2.M31 + M14 * matrix2.M41);
	matrix.M12 = (M11 * matrix2.M12 + M12 * matrix2.M22 + M13 * matrix2.M32 + M14 * matrix2.M42);
	matrix.M13 = (M11 * matrix2.M13 + M12 * matrix2.M23 + M13 * matrix2.M33 + M14 * matrix2.M43);
	matrix.M14 = (M11 * matrix2.M14 + M12 * matrix2.M24 + M13 * matrix2.M34 + M14 * matrix2.M44);
	matrix.M21 = (M21 * matrix2.M11 + M22 * matrix2.M21 + M23 * matrix2.M31 + M24 * matrix2.M41);
	matrix.M22 = (M21 * matrix2.M12 + M22 * matrix2.M22 + M23 * matrix2.M32 + M24 * matrix2.M42);
	matrix.M23 = (M21 * matrix2.M13 + M22 * matrix2.M23 + M23 * matrix2.M33 + M24 * matrix2.M43);
	matrix.M24 = (M21 * matrix2.M14 + M22 * matrix2.M24 + M23 * matrix2.M34 + M24 * matrix2.M44);
	matrix.M31 = (M31 * matrix2.M11 + M32 * matrix2.M21 + M33 * matrix2.M31 + M34 * matrix2.M41);
	matrix.M32 = (M31 * matrix2.M12 + M32 * matrix2.M22 + M33 * matrix2.M32 + M34 * matrix2.M42);
	matrix.M33 = (M31 * matrix2.M13 + M32 * matrix2.M23 + M33 * matrix2.M33 + M34 * matrix2.M43);
	matrix.M34 = (M31 * matrix2.M14 + M32 * matrix2.M24 + M33 * matrix2.M34 + M34 * matrix2.M44);
	matrix.M41 = (M41 * matrix2.M11 + M42 * matrix2.M21 + M43 * matrix2.M31 + M44 * matrix2.M41);
	matrix.M42 = (M41 * matrix2.M12 + M42 * matrix2.M22 + M43 * matrix2.M32 + M44 * matrix2.M42);
	matrix.M43 = (M41 * matrix2.M13 + M42 * matrix2.M23 + M43 * matrix2.M33 + M44 * matrix2.M43);
	matrix.M44 = (M41 * matrix2.M14 + M42 * matrix2.M24 + M43 * matrix2.M34 + M44 * matrix2.M44);

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator*(const float& scaleFactor) const
{
	float num = scaleFactor;
	FMatrix matrix1;

	matrix1.M11 = M11 * num; matrix1.M12 = M12 * num; matrix1.M13 = M13 * num; matrix1.M14 = M14 * num;
	matrix1.M21 = M21 * num; matrix1.M22 = M22 * num; matrix1.M23 = M23 * num; matrix1.M24 = M24 * num;
	matrix1.M31 = M31 * num; matrix1.M32 = M32 * num; matrix1.M33 = M33 * num; matrix1.M34 = M34 * num;
	matrix1.M41 = M41 * num; matrix1.M42 = M42 * num; matrix1.M43 = M43 * num; matrix1.M44 = M44 * num;

	return matrix1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator/(const FMatrix& matrix2) const
{
	FMatrix matrix;
	matrix.M11 = M11 / matrix2.M11; matrix.M12 = M12 / matrix2.M12; matrix.M13 = M13 / matrix2.M13; matrix.M14 = M14 / matrix2.M14;
	matrix.M21 = M21 / matrix2.M21; matrix.M22 = M22 / matrix2.M22; matrix.M23 = M23 / matrix2.M23; matrix.M24 = M24 / matrix2.M24;
	matrix.M31 = M31 / matrix2.M31; matrix.M32 = M32 / matrix2.M32; matrix.M33 = M33 / matrix2.M33; matrix.M34 = M34 / matrix2.M34;
	matrix.M41 = M41 / matrix2.M41; matrix.M42 = M42 / matrix2.M42; matrix.M43 = M43 / matrix2.M43; matrix.M44 = M44 / matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param divider : ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::operator/(const float& divider) const
{
	float num = 1.0f / divider;

	FMatrix matrix;
	matrix.M11 = M11 * num; matrix.M12 = M12 * num; matrix.M13 = M13 * num; matrix.M14 = M14 * num;
	matrix.M21 = M21 * num; matrix.M22 = M22 * num; matrix.M23 = M23 * num; matrix.M24 = M24 * num;
	matrix.M31 = M31 * num; matrix.M32 = M32 * num; matrix.M33 = M33 * num; matrix.M34 = M34 * num;
	matrix.M41 = M41 * num; matrix.M42 = M42 * num; matrix.M43 = M43 * num; matrix.M44 = M44 * num;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator+=(const FMatrix& matrix2)
{
	*this = *this + matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator-=(const FMatrix& matrix2)
{
	*this = *this - matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator*=(const FMatrix& matrix2)
{
	*this = *this * matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param scaleFactor : ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator*=(const float& scaleFactor)
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param matrix2 : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator/=(const FMatrix& matrix2)
{
	*this = *this / matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param divider : ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void FMatrix::operator/=(const float& divider)
{
	*this = *this / divider;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ��� ��ȯ
///@return ���ڿ�
//////////////////////////////////////////////////////////////////////////
std::string FMatrix::ToString()
{
	std::string temp = "";

	temp += ToStringRow1();
	temp += ToStringRow2();
	temp += ToStringRow3();
	temp += ToStringRow4();

	return temp;
}

std::string FMatrix::ToStringRow1()
{
	std::string temp = "";

	temp += " M11:" + std::to_string(M11);
	temp += ",M12:" + std::to_string(M12);
	temp += ",M13:" + std::to_string(M13);
	temp += ",M14:" + std::to_string(M14);

	return temp;
}

std::string FMatrix::ToStringRow2()
{
	std::string temp = "";

	temp += " M21:" + std::to_string(M21);
	temp += ",M22:" + std::to_string(M22);
	temp += ",M23:" + std::to_string(M23);
	temp += ",M24:" + std::to_string(M24);

	return temp;
}

std::string FMatrix::ToStringRow3()
{
	std::string temp = "";

	temp += " M31:" + std::to_string(M31);
	temp += ",M32:" + std::to_string(M32);
	temp += ",M33:" + std::to_string(M33);
	temp += ",M34:" + std::to_string(M34);

	return temp;
}

std::string FMatrix::ToStringRow4()
{
	std::string temp = "";

	temp += " M41:" + std::to_string(M41);
	temp += ",M42:" + std::to_string(M42);
	temp += ",M43:" + std::to_string(M43);
	temp += ",M44:" + std::to_string(M44);

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ľ�
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
float FMatrix::Determinant()
{
	float value1 = (float)(M33 * M44 - M34 * M43);
	float value2 = (float)(M32 * M44 - M34 * M42);
	float value3 = (float)(M32 * M43 - M33 * M42);
	float value4 = (float)(M31 * M44 - M34 * M41);
	float value5 = (float)(M31 * M43 - M33 * M41);
	float value6 = (float)(M31 * M42 - M32 * M41);

	float temp =
		(float)(M11 * (M22 * value1 - M23 * value2 + M24 * value3) -
			M12 * (M21 * value1 - M23 * value4 + M24 * value5) +
			M13 * (M21 * value2 - M22 * value4 + M24 * value6) -
			M14 * (M21 * value3 - M22 * value5 + M23 * value6));

	return temp;
}

bool FMatrix::Decompose(FVector& scale, FQuaternion& rotation, FVector& translation)
{
	translation.X = M41;
	translation.Y = M42;
	translation.Z = M43;

	scale.X = sqrtf((M11 * M11) + (M12 * M12) + (M13 * M13));
	scale.Y = sqrtf((M21 * M21) + (M22 * M22) + (M23 * M23));
	scale.Z = sqrtf((M31 * M31) + (M32 * M32) + (M33 * M33));

	if (FMath::IsZero(scale.X) || FMath::IsZero(scale.Y) || FMath::IsZero(scale.Z))
	{
		rotation = FQuaternion::Identity;

		return false;
	}


	FMatrix rotationmatrix;

	rotationmatrix.M11 = M11 / scale.X;
	rotationmatrix.M12 = M12 / scale.X;
	rotationmatrix.M13 = M13 / scale.X;

	rotationmatrix.M21 = M21 / scale.Y;
	rotationmatrix.M22 = M22 / scale.Y;
	rotationmatrix.M23 = M23 / scale.Y;

	rotationmatrix.M31 = M31 / scale.Z;
	rotationmatrix.M32 = M32 / scale.Z;
	rotationmatrix.M33 = M33 / scale.Z;

	rotationmatrix.M44 = 1.0f;

	rotation = FQuaternion::CreateFromRotationMatrix(rotationmatrix);

	return true;
}

bool FMatrix::DecomposeUniformScale(float& scale, FQuaternion& rotation, FVector& translation)
{
	translation.X = M41;
	translation.Y = M42;
	translation.Z = M43;

	scale = sqrtf((M11 * M11) + (M12 * M12) + (M13 * M13));
	float inv_scale = 1.0f / scale;

	if (fabsf(scale) < FMath::Epsilon)
	{
		rotation = FQuaternion::Identity;

		return false;
	}


	FMatrix rotationmatrix;
	rotationmatrix.M11 = M11 * inv_scale;
	rotationmatrix.M12 = M12 * inv_scale;
	rotationmatrix.M13 = M13 * inv_scale;

	rotationmatrix.M21 = M21 * inv_scale;
	rotationmatrix.M22 = M22 * inv_scale;
	rotationmatrix.M23 = M23 * inv_scale;

	rotationmatrix.M31 = M31 * inv_scale;
	rotationmatrix.M32 = M32 * inv_scale;
	rotationmatrix.M33 = M33 * inv_scale;

	rotationmatrix.M44 = 1.0f;

	rotation = FQuaternion::CreateFromRotationMatrix(rotationmatrix);

	return true;
}

FMatrix FMatrix::Add(FMatrix matrix1, FMatrix matrix2)
{
	FMatrix matrix;
	matrix.M11 = matrix1.M11 + matrix2.M11;
	matrix.M12 = matrix1.M12 + matrix2.M12;
	matrix.M13 = matrix1.M13 + matrix2.M13;
	matrix.M14 = matrix1.M14 + matrix2.M14;
	matrix.M21 = matrix1.M21 + matrix2.M21;
	matrix.M22 = matrix1.M22 + matrix2.M22;
	matrix.M23 = matrix1.M23 + matrix2.M23;
	matrix.M24 = matrix1.M24 + matrix2.M24;
	matrix.M31 = matrix1.M31 + matrix2.M31;
	matrix.M32 = matrix1.M32 + matrix2.M32;
	matrix.M33 = matrix1.M33 + matrix2.M33;
	matrix.M34 = matrix1.M34 + matrix2.M34;
	matrix.M41 = matrix1.M41 + matrix2.M41;
	matrix.M42 = matrix1.M42 + matrix2.M42;
	matrix.M43 = matrix1.M43 + matrix2.M43;
	matrix.M44 = matrix1.M44 + matrix2.M44;

	return matrix;
}

FMatrix FMatrix::Divide(FMatrix matrix1, FMatrix matrix2)
{
	FMatrix matrix;
	matrix.M11 = matrix1.M11 / matrix2.M11;
	matrix.M12 = matrix1.M12 / matrix2.M12;
	matrix.M13 = matrix1.M13 / matrix2.M13;
	matrix.M14 = matrix1.M14 / matrix2.M14;
	matrix.M21 = matrix1.M21 / matrix2.M21;
	matrix.M22 = matrix1.M22 / matrix2.M22;
	matrix.M23 = matrix1.M23 / matrix2.M23;
	matrix.M24 = matrix1.M24 / matrix2.M24;
	matrix.M31 = matrix1.M31 / matrix2.M31;
	matrix.M32 = matrix1.M32 / matrix2.M32;
	matrix.M33 = matrix1.M33 / matrix2.M33;
	matrix.M34 = matrix1.M34 / matrix2.M34;
	matrix.M41 = matrix1.M41 / matrix2.M41;
	matrix.M42 = matrix1.M42 / matrix2.M42;
	matrix.M43 = matrix1.M43 / matrix2.M43;
	matrix.M44 = matrix1.M44 / matrix2.M44;

	return matrix;
}

FMatrix FMatrix::Divide(FMatrix matrix1, float divider)
{
	FMatrix matrix;
	float value = 1.0f / divider;
	matrix.M11 = matrix1.M11 * value;
	matrix.M12 = matrix1.M12 * value;
	matrix.M13 = matrix1.M13 * value;
	matrix.M14 = matrix1.M14 * value;
	matrix.M21 = matrix1.M21 * value;
	matrix.M22 = matrix1.M22 * value;
	matrix.M23 = matrix1.M23 * value;
	matrix.M24 = matrix1.M24 * value;
	matrix.M31 = matrix1.M31 * value;
	matrix.M32 = matrix1.M32 * value;
	matrix.M33 = matrix1.M33 * value;
	matrix.M34 = matrix1.M34 * value;
	matrix.M41 = matrix1.M41 * value;
	matrix.M42 = matrix1.M42 * value;
	matrix.M43 = matrix1.M43 * value;
	matrix.M44 = matrix1.M44 * value;

	return matrix;
}

FMatrix FMatrix::Multiply(FMatrix matrix1, FMatrix matrix2)
{
	FMatrix matrix;
	matrix.M11 = matrix1.M11 * matrix2.M11 + matrix1.M12 * matrix2.M21 + matrix1.M13 * matrix2.M31 + matrix1.M14 * matrix2.M41;
	matrix.M12 = matrix1.M11 * matrix2.M12 + matrix1.M12 * matrix2.M22 + matrix1.M13 * matrix2.M32 + matrix1.M14 * matrix2.M42;
	matrix.M13 = matrix1.M11 * matrix2.M13 + matrix1.M12 * matrix2.M23 + matrix1.M13 * matrix2.M33 + matrix1.M14 * matrix2.M43;
	matrix.M14 = matrix1.M11 * matrix2.M14 + matrix1.M12 * matrix2.M24 + matrix1.M13 * matrix2.M34 + matrix1.M14 * matrix2.M44;
	matrix.M21 = matrix1.M21 * matrix2.M11 + matrix1.M22 * matrix2.M21 + matrix1.M23 * matrix2.M31 + matrix1.M24 * matrix2.M41;
	matrix.M22 = matrix1.M21 * matrix2.M12 + matrix1.M22 * matrix2.M22 + matrix1.M23 * matrix2.M32 + matrix1.M24 * matrix2.M42;
	matrix.M23 = matrix1.M21 * matrix2.M13 + matrix1.M22 * matrix2.M23 + matrix1.M23 * matrix2.M33 + matrix1.M24 * matrix2.M43;
	matrix.M24 = matrix1.M21 * matrix2.M14 + matrix1.M22 * matrix2.M24 + matrix1.M23 * matrix2.M34 + matrix1.M24 * matrix2.M44;
	matrix.M31 = matrix1.M31 * matrix2.M11 + matrix1.M32 * matrix2.M21 + matrix1.M33 * matrix2.M31 + matrix1.M34 * matrix2.M41;
	matrix.M32 = matrix1.M31 * matrix2.M12 + matrix1.M32 * matrix2.M22 + matrix1.M33 * matrix2.M32 + matrix1.M34 * matrix2.M42;
	matrix.M33 = matrix1.M31 * matrix2.M13 + matrix1.M32 * matrix2.M23 + matrix1.M33 * matrix2.M33 + matrix1.M34 * matrix2.M43;
	matrix.M34 = matrix1.M31 * matrix2.M14 + matrix1.M32 * matrix2.M24 + matrix1.M33 * matrix2.M34 + matrix1.M34 * matrix2.M44;
	matrix.M41 = matrix1.M41 * matrix2.M11 + matrix1.M42 * matrix2.M21 + matrix1.M43 * matrix2.M31 + matrix1.M44 * matrix2.M41;
	matrix.M42 = matrix1.M41 * matrix2.M12 + matrix1.M42 * matrix2.M22 + matrix1.M43 * matrix2.M32 + matrix1.M44 * matrix2.M42;
	matrix.M43 = matrix1.M41 * matrix2.M13 + matrix1.M42 * matrix2.M23 + matrix1.M43 * matrix2.M33 + matrix1.M44 * matrix2.M43;
	matrix.M44 = matrix1.M41 * matrix2.M14 + matrix1.M42 * matrix2.M24 + matrix1.M43 * matrix2.M34 + matrix1.M44 * matrix2.M44;

	return matrix;
}

FMatrix FMatrix::Multiply(FMatrix matrix1, float scaleFactor)
{
	FMatrix matrix;
	float value = scaleFactor;
	matrix.M11 = matrix1.M11 * value;
	matrix.M12 = matrix1.M12 * value;
	matrix.M13 = matrix1.M13 * value;
	matrix.M14 = matrix1.M14 * value;
	matrix.M21 = matrix1.M21 * value;
	matrix.M22 = matrix1.M22 * value;
	matrix.M23 = matrix1.M23 * value;
	matrix.M24 = matrix1.M24 * value;
	matrix.M31 = matrix1.M31 * value;
	matrix.M32 = matrix1.M32 * value;
	matrix.M33 = matrix1.M33 * value;
	matrix.M34 = matrix1.M34 * value;
	matrix.M41 = matrix1.M41 * value;
	matrix.M42 = matrix1.M42 * value;
	matrix.M43 = matrix1.M43 * value;
	matrix.M44 = matrix1.M44 * value;

	return matrix;
}

FMatrix FMatrix::Negative(FMatrix matrix)
{
	FMatrix m;
	m.M11 = -matrix.M11;
	m.M12 = -matrix.M12;
	m.M13 = -matrix.M13;
	m.M14 = -matrix.M14;
	m.M21 = -matrix.M21;
	m.M22 = -matrix.M22;
	m.M23 = -matrix.M23;
	m.M24 = -matrix.M24;
	m.M31 = -matrix.M31;
	m.M32 = -matrix.M32;
	m.M33 = -matrix.M33;
	m.M34 = -matrix.M34;
	m.M41 = -matrix.M41;
	m.M42 = -matrix.M42;
	m.M43 = -matrix.M43;
	m.M44 = -matrix.M44;

	return m;
}


//////////////////////////////////////////////////////////////////////////
///@brief ������ ��Ʈ���� ����
///@param objectPosition : ������Ʈ ��ġ
///@param cameraPosition : ī�޶� ��ġ
///@param cameraUpVector : ī�޶� ������
///@param cameraForwardVector : ī�޶� �����庤��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateBillboard(FVector objectPosition, FVector cameraPosition, FVector cameraUpVector, FVector* cameraForwardVector/*=NULL*/)
{
	FVector zAxis;
	FVector xAxis;
	FVector yAxis;
	zAxis.X = objectPosition.X - cameraPosition.X;
	zAxis.Y = objectPosition.Y - cameraPosition.Y;
	zAxis.Z = objectPosition.Z - cameraPosition.Z;

	float length = zAxis.LengthSquared();
	if (length >= 0.0001f)
	{
		zAxis = FVector::Multiply(zAxis, 1.0f / sqrtf(length));
	}
	else
	{
		zAxis = (cameraForwardVector != NULL ? (*cameraForwardVector) : FVector::Forward);
	}


	yAxis = FVector::Cross(cameraUpVector, zAxis);
	yAxis.Normalize();
	xAxis = FVector::Cross(zAxis, yAxis);

	FMatrix matrix;
	matrix.M11 = yAxis.X; matrix.M12 = yAxis.Y; matrix.M13 = yAxis.Z; matrix.M14 = 0.0f;
	matrix.M21 = xAxis.X; matrix.M22 = xAxis.Y; matrix.M23 = xAxis.Z; matrix.M24 = 0.0f;
	matrix.M31 = zAxis.X; matrix.M32 = zAxis.Y; matrix.M33 = zAxis.Z; matrix.M34 = 0.0f;

	matrix.M41 = objectPosition.X;
	matrix.M42 = objectPosition.Y;
	matrix.M43 = objectPosition.Z;
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �̵� ��Ʈ���� ����
///@param position : ��ġ
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateTranslation(FVector position)
{
	FMatrix matrix;

	matrix.M11 = 1.0f; matrix.M12 = 0.0f; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;

	matrix.M41 = position.X;
	matrix.M42 = position.Y;
	matrix.M43 = position.Z;
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �̵� ��Ʈ���� ����
///@param xPosition : x ��ġ
///@param yPosition : y ��ġ
///@param zPosition : z ��ġ
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateTranslation(float xPosition, float yPosition, float zPosition)
{
	FMatrix matrix;

	matrix.M11 = 1.0f; matrix.M12 = 0.0f; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;

	matrix.M41 = xPosition;
	matrix.M42 = yPosition;
	matrix.M43 = zPosition;
	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ũ�� ��Ʈ���� ����
///@param scales : ũ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateScale(FVector scales)
{
	FMatrix matrix;
	matrix.M11 = scales.X; matrix.M12 = 0.0f;     matrix.M13 = 0.0f;     matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;     matrix.M22 = scales.Y; matrix.M23 = 0.0f;     matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;     matrix.M32 = 0.0f;     matrix.M33 = scales.Z; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;     matrix.M42 = 0.0f;     matrix.M43 = 0.0f;     matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ũ�� ��Ʈ���� ����
///@param xScale : x ũ��
///@param yScale : y ũ��
///@param zScale : z ũ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateScale(float xScale, float yScale, float zScale)
{
	FMatrix matrix;
	matrix.M11 = xScale; matrix.M12 = 0.0f;   matrix.M13 = 0.0f;   matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;   matrix.M22 = yScale; matrix.M23 = 0.0f;   matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;   matrix.M32 = 0.0f;   matrix.M33 = zScale; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;   matrix.M42 = 0.0f;   matrix.M43 = 0.0f;   matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ũ�� ��Ʈ���� ����
///@param scale : ũ�Ⱚ
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateScale(float scale)
{
	FMatrix matrix;
	matrix.M11 = scale; matrix.M12 = 0.0f;  matrix.M13 = 0.0f;  matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;  matrix.M22 = scale; matrix.M23 = 0.0f;  matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;  matrix.M32 = 0.0f;  matrix.M33 = scale; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;  matrix.M42 = 0.0f;  matrix.M43 = 0.0f;  matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief X�� ȸ�� ��Ʈ���� ����
///@param radians : ���� ������
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateRotationX(float radians)
{
	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	FMatrix matrix;
	matrix.M11 = 1.0f; matrix.M12 = 0.0f;  matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = val1;  matrix.M23 = val2; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = -val2; matrix.M33 = val1; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f;  matrix.M43 = 0.0f; matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Y�� ȸ�� ��Ʈ���� ����
///@param radians : ���� ������
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateRotationY(float radians)
{
	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	FMatrix matrix;
	matrix.M11 = val1; matrix.M12 = 0.0f; matrix.M13 = -val2; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f;  matrix.M24 = 0.0f;
	matrix.M31 = val2; matrix.M32 = 0.0f; matrix.M33 = val1;  matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f; matrix.M43 = 0.0f;  matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Z�� ȸ�� ��Ʈ���� ����
///@param radians : ���� ������
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateRotationZ(float radians)
{
	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	FMatrix matrix;
	matrix.M11 = val1;  matrix.M12 = val2; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = -val2; matrix.M22 = val1; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;  matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;  matrix.M42 = 0.0f; matrix.M43 = 0.0f; matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ���� ȸ�� ��Ʈ���� ����
///@param axis : ��
///@param angle : ȸ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateFromAxisAngle(FVector axis, float angle)
{
	FMatrix matrix;
	float x = axis.X;
	float y = axis.Y;
	float z = axis.Z;

	float value = (float)sin(angle);
	float value1 = (float)cos(angle);
	float value2 = x * x;
	float value3 = y * y;
	float value4 = z * z;
	float value5 = x * y;
	float value6 = x * z;
	float value7 = y * z;

	matrix.M11 = value2 + value1 * (1.0f - value2);
	matrix.M12 = value5 - value1 * value5 + value * z;
	matrix.M13 = value6 - value1 * value6 - value * y;
	matrix.M14 = 0.0f;

	matrix.M21 = value5 - value1 * value5 - value * z;
	matrix.M22 = value3 + value1 * (1.0f - value3);
	matrix.M23 = value7 - value1 * value7 + value * x;
	matrix.M24 = 0.0f;

	matrix.M31 = value6 - value1 * value6 + value * y;
	matrix.M32 = value7 - value1 * value7 - value * x;
	matrix.M33 = value4 + value1 * (1.0f - value4);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �������� ��Ʈ���� ����
///@param width : ȭ�����
///@param height : ȭ�����
///@param nearPlaneDistance : �ٸ�Ÿ�
///@param farPlaneDistance : ����Ÿ�
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	//assert(nearPlaneDistance > 0.0);
	//assert(farPlaneDistance > 0.0);
	//assert(nearPlaneDistance < farPlaneDistance);

	FMatrix matrix;
	matrix.M11 = 2.0f * nearPlaneDistance / width;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f * nearPlaneDistance / height;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	matrix.M44 = 0.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief FOV�� �������� �������� ��Ʈ���� ����
///@param fieldOfView : FOV
///@param aspectRatio : ȭ�����
///@param nearPlaneDistance : �ٸ�Ÿ�
///@param farPlaneDistance : ����Ÿ�
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
	//assert(fieldOfView > 0.0 || fieldOfView < 3.14159274101257);
	//assert(nearPlaneDistance > 0.0);
	//assert(farPlaneDistance > 0.0);
	//assert(nearPlaneDistance < farPlaneDistance);

	float yScale = 1.0f / (float)tan(fieldOfView * 0.5); //cot
	float xScale = yScale / aspectRatio;

	FMatrix matrix;
	matrix.M11 = xScale;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = yScale;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = -nearPlaneDistance * farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
	matrix.M44 = 0.0f;

	return matrix;
}

FMatrix FMatrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
{
	//assert(nearPlaneDistance > 0.0);
	//assert(farPlaneDistance > 0.0);
	//assert(nearPlaneDistance < farPlaneDistance);


	FMatrix matrix;
	matrix.M11 = 2.0f * nearPlaneDistance / (right - left);;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f * nearPlaneDistance / (top - bottom);;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = (left + right) / (left - right);
	matrix.M32 = (top + bottom) / (bottom - top);
	matrix.M33 = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	matrix.M44 = 0.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���(��) ��Ʈ���� ����
///@param cameraPosition : ī�޶� ��ġ
///@param cameraTarget : ī�޶� Ÿ��
///@param cameraUpVector : ī�޶� ������
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateLookAt(FVector cameraPosition, FVector cameraTarget, FVector cameraUpVector)
{
	FMatrix matrix;
	FVector zAxis = FVector::Normalize(cameraTarget - cameraPosition);
	FVector xAxis = FVector::Normalize(FVector::Cross(cameraUpVector, zAxis));
	FVector yAxis = FVector::Cross(zAxis, xAxis);

	matrix.M11 = xAxis.X; matrix.M12 = yAxis.X; matrix.M13 = zAxis.X; matrix.M14 = 0.0f;
	matrix.M21 = xAxis.Y; matrix.M22 = yAxis.Y; matrix.M23 = zAxis.Y; matrix.M24 = 0.0f;
	matrix.M31 = xAxis.Z; matrix.M32 = yAxis.Z; matrix.M33 = zAxis.Z; matrix.M34 = 0.0f;

	matrix.M41 = -FVector::Dot(xAxis, cameraPosition);
	matrix.M42 = -FVector::Dot(yAxis, cameraPosition);
	matrix.M43 = -FVector::Dot(zAxis, cameraPosition);
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���� ��Ʈ���� ����
///@param position : ��ġ
///@param forward : ���� ����
///@param up : ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateWorld(FVector position, FVector forward, FVector up)
{
	FVector zAxis = FVector::Normalize(forward);
	FVector xAxis = FVector::Normalize(FVector::Cross(up, zAxis));
	FVector yAxis = FVector::Cross(zAxis, xAxis);

	FMatrix matrix;
	matrix.M11 = xAxis.X; matrix.M12 = xAxis.Y; matrix.M13 = xAxis.Z; matrix.M14 = 0.0f;
	matrix.M21 = yAxis.X; matrix.M22 = yAxis.Y; matrix.M23 = yAxis.Z; matrix.M24 = 0.0f;
	matrix.M31 = zAxis.X; matrix.M32 = zAxis.Y; matrix.M33 = zAxis.Z; matrix.M34 = 0.0f;
	matrix.M41 = position.X; matrix.M42 = position.Y; matrix.M43 = position.Z; matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ʹϿ����κ��� ��Ʈ���� ����
///@param quaternion : ���ʹϿ�
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateFromQuaternion(FQuaternion quaternion)
{
	float x = quaternion.X * quaternion.X;
	float y = quaternion.Y * quaternion.Y;
	float z = quaternion.Z * quaternion.Z;
	float value = quaternion.X * quaternion.Y;
	float z1 = quaternion.Z * quaternion.W;
	float value1 = quaternion.Z * quaternion.X;
	float y1 = quaternion.Y * quaternion.W;
	float y2 = quaternion.Y * quaternion.Z;
	float x1 = quaternion.X * quaternion.W;


	FMatrix matrix;
	matrix.M11 = 1.0f - 2.0f * (y + z);
	matrix.M12 = 2.0f * (value + z1);
	matrix.M13 = 2.0f * (value1 - y1);
	matrix.M14 = 0.0f;

	matrix.M21 = 2.0f * (value - z1);
	matrix.M22 = 1.0f - 2.0f * (z + x);
	matrix.M23 = 2.0f * (y2 + x1);
	matrix.M24 = 0.0f;

	matrix.M31 = 2.0f * (value1 + y1);
	matrix.M32 = 2.0f * (y2 - x1);
	matrix.M33 = 1.0f - 2.0f * (y + x);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� �ప�� ���� ȸ�� ��Ʈ���� ����(���ʹϿ� �̿�)
///@param yaw : Yaw
///@param pitch : Pitch
///@param roll : Roll
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	FQuaternion result1;
	result1 = FQuaternion::CreateFromYawPitchRoll(yaw, pitch, roll);

	FMatrix result2;
	result2 = CreateFromQuaternion(result1);

	return result2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���絵���� ���� ��� ����
///@param width : ����
///@param height : ����
///@param zNearPlane : z���� �ٸ�
///@param zFarPlane : z���� ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
	FMatrix matrix;

	matrix.M11 = 2.0f / width;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f / height;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = 1.0f / (zNearPlane - zFarPlane);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = zNearPlane / (zNearPlane - zFarPlane);
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
	FMatrix matrix;

	matrix.M11 = 2.0f / (right - left);
	matrix.M12 = 0.0;
	matrix.M13 = 0.0;
	matrix.M14 = 0.0;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f / (top - bottom);
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = 1.0f / (zNearPlane - zFarPlane);
	matrix.M34 = 0.0f;

	matrix.M41 = (left + right) / (left - right);
	matrix.M42 = (top + bottom) / (bottom - top);
	matrix.M43 = zNearPlane / (zNearPlane - zFarPlane);
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
///@brief ���ʹϿ¿� ���� ��Ʈ���� ��ȯ
///@param value : ��Ʈ����
///@param rotation : ���ʹϿ�
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::Transform(FMatrix value, FQuaternion rotation)
{
	float wxx = rotation.W * (rotation.X + rotation.X);
	float wyy = rotation.W * (rotation.Y + rotation.Y);
	float wzz = rotation.W * (rotation.Z + rotation.Z);

	float xxx = rotation.X * (rotation.X + rotation.X);
	float xyy = rotation.X * (rotation.Y + rotation.Y);
	float xzz = rotation.X * (rotation.Z + rotation.Z);

	float yyy = rotation.Y * (rotation.Y + rotation.Y);
	float yzz = rotation.Y * (rotation.Z + rotation.Z);
	float zzz = rotation.Z * (rotation.Z + rotation.Z);

	float value1 = 1.0f - yyy - zzz;
	float value2 = xyy - wzz;
	float value3 = xzz + wyy;
	float value4 = xyy + wzz;

	float value5 = 1.0f - xxx - zzz;
	float value6 = yzz - wxx;
	float value7 = xzz - wyy;
	float value8 = yzz + wxx;

	float value9 = 1.0f - xxx - yyy;

	FMatrix matrix;
	matrix.M11 = (float)(value.M11 * value1 + value.M12 * value2 + value.M13 * value3);
	matrix.M12 = (float)(value.M11 * value4 + value.M12 * value5 + value.M13 * value6);
	matrix.M13 = (float)(value.M11 * value7 + value.M12 * value8 + value.M13 * value9);
	matrix.M14 = value.M14;

	matrix.M21 = (float)(value.M21 * value1 + value.M22 * value2 + value.M23 * value3);
	matrix.M22 = (float)(value.M21 * value4 + value.M22 * value5 + value.M23 * value6);
	matrix.M23 = (float)(value.M21 * value7 + value.M22 * value8 + value.M23 * value9);
	matrix.M24 = value.M24;

	matrix.M31 = (float)(value.M31 * value1 + value.M32 * value2 + value.M33 * value3);
	matrix.M32 = (float)(value.M31 * value4 + value.M32 * value5 + value.M33 * value6);
	matrix.M33 = (float)(value.M31 * value7 + value.M32 * value8 + value.M33 * value9);
	matrix.M34 = value.M34;

	matrix.M41 = (float)(value.M41 * value1 + value.M42 * value2 + value.M43 * value3);
	matrix.M42 = (float)(value.M41 * value4 + value.M42 * value5 + value.M43 * value6);
	matrix.M43 = (float)(value.M41 * value7 + value.M42 * value8 + value.M43 * value9);
	matrix.M44 = value.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��ġ ��Ʈ����
///@param matrix : ���
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::Transpose(FMatrix matrix)
{
	FMatrix matrix1;
	matrix1.M11 = matrix.M11; matrix1.M12 = matrix.M21; matrix1.M13 = matrix.M31; matrix1.M14 = matrix.M41;
	matrix1.M21 = matrix.M12; matrix1.M22 = matrix.M22; matrix1.M23 = matrix.M32; matrix1.M24 = matrix.M42;
	matrix1.M31 = matrix.M13; matrix1.M32 = matrix.M23; matrix1.M33 = matrix.M33; matrix1.M34 = matrix.M43;
	matrix1.M41 = matrix.M14; matrix1.M42 = matrix.M24; matrix1.M43 = matrix.M34; matrix1.M44 = matrix.M44;

	return matrix1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �����
///@param matrix : ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::Invert(FMatrix matrix)
{
	float value5 = matrix.M11; float value4 = matrix.M12; float value3 = matrix.M13; float value2 = matrix.M14;
	float value9 = matrix.M21; float value8 = matrix.M22; float value7 = matrix.M23; float value6 = matrix.M24;
	float value17 = matrix.M31; float value16 = matrix.M32; float value15 = matrix.M33; float value14 = matrix.M34;
	float value13 = matrix.M41; float value12 = matrix.M42; float value11 = matrix.M43; float value10 = matrix.M44;

	float value23 = (value15 * value10) - (value14 * value11);
	float value22 = (value16 * value10) - (value14 * value12);
	float value21 = (value16 * value11) - (value15 * value12);
	float value20 = (value17 * value10) - (value14 * value13);
	float value19 = (value17 * value11) - (value15 * value13);
	float value18 = (value17 * value12) - (value16 * value13);
	float value39 = ((value8 * value23) - (value7 * value22)) + (value6 * value21);
	float value38 = -(((value9 * value23) - (value7 * value20)) + (value6 * value19));
	float value37 = ((value9 * value22) - (value8 * value20)) + (value6 * value18);
	float value36 = -(((value9 * value21) - (value8 * value19)) + (value7 * value18));
	float value = 1.0f / ((((value5 * value39) + (value4 * value38)) + (value3 * value37)) + (value2 * value36));


	FMatrix matrix2;

	matrix2.M11 = value39 * value;
	matrix2.M21 = value38 * value;
	matrix2.M31 = value37 * value;
	matrix2.M41 = value36 * value;

	matrix2.M12 = -(((value4 * value23) - (value3 * value22)) + (value2 * value21)) * value;
	matrix2.M22 = (((value5 * value23) - (value3 * value20)) + (value2 * value19)) * value;
	matrix2.M32 = -(((value5 * value22) - (value4 * value20)) + (value2 * value18)) * value;
	matrix2.M42 = (((value5 * value21) - (value4 * value19)) + (value3 * value18)) * value;

	float value35 = (value7 * value10) - (value6 * value11);
	float value34 = (value8 * value10) - (value6 * value12);
	float value33 = (value8 * value11) - (value7 * value12);
	float value32 = (value9 * value10) - (value6 * value13);
	float value31 = (value9 * value11) - (value7 * value13);
	float value30 = (value9 * value12) - (value8 * value13);

	matrix2.M13 = (((value4 * value35) - (value3 * value34)) + (value2 * value33)) * value;
	matrix2.M23 = -(((value5 * value35) - (value3 * value32)) + (value2 * value31)) * value;
	matrix2.M33 = (((value5 * value34) - (value4 * value32)) + (value2 * value30)) * value;
	matrix2.M43 = -(((value5 * value33) - (value4 * value31)) + (value3 * value30)) * value;

	float value29 = (value7 * value14) - (value6 * value15);
	float value28 = (value8 * value14) - (value6 * value16);
	float value27 = (value8 * value15) - (value7 * value16);
	float value26 = (value9 * value14) - (value6 * value17);
	float value25 = (value9 * value15) - (value7 * value17);
	float value24 = (value9 * value16) - (value8 * value17);

	matrix2.M14 = -(((value4 * value29) - (value3 * value28)) + (value2 * value27)) * value;
	matrix2.M24 = (((value5 * value29) - (value3 * value26)) + (value2 * value25)) * value;
	matrix2.M34 = -(((value5 * value28) - (value4 * value26)) + (value2 * value24)) * value;
	matrix2.M44 = (((value5 * value27) - (value4 * value25)) + (value3 * value24)) * value;

	return matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ��Ʈ������ ��������
///@param matrix1 : ��Ʈ����1
///@param matrix2 : ��Ʈ����2
///@param amount : ���� ��
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
FMatrix FMatrix::Lerp(FMatrix matrix1, FMatrix matrix2, float amount)
{
	FMatrix matrix;
	matrix.M11 = matrix1.M11 + (matrix2.M11 - matrix1.M11) * amount;
	matrix.M12 = matrix1.M12 + (matrix2.M12 - matrix1.M12) * amount;
	matrix.M13 = matrix1.M13 + (matrix2.M13 - matrix1.M13) * amount;
	matrix.M14 = matrix1.M14 + (matrix2.M14 - matrix1.M14) * amount;
	matrix.M21 = matrix1.M21 + (matrix2.M21 - matrix1.M21) * amount;
	matrix.M22 = matrix1.M22 + (matrix2.M22 - matrix1.M22) * amount;
	matrix.M23 = matrix1.M23 + (matrix2.M23 - matrix1.M23) * amount;
	matrix.M24 = matrix1.M24 + (matrix2.M24 - matrix1.M24) * amount;
	matrix.M31 = matrix1.M31 + (matrix2.M31 - matrix1.M31) * amount;
	matrix.M32 = matrix1.M32 + (matrix2.M32 - matrix1.M32) * amount;
	matrix.M33 = matrix1.M33 + (matrix2.M33 - matrix1.M33) * amount;
	matrix.M34 = matrix1.M34 + (matrix2.M34 - matrix1.M34) * amount;
	matrix.M41 = matrix1.M41 + (matrix2.M41 - matrix1.M41) * amount;
	matrix.M42 = matrix1.M42 + (matrix2.M42 - matrix1.M42) * amount;
	matrix.M43 = matrix1.M43 + (matrix2.M43 - matrix1.M43) * amount;
	matrix.M44 = matrix1.M44 + (matrix2.M44 - matrix1.M44) * amount;

	return matrix;
}