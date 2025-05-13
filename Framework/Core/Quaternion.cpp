#include "Framework.h"
#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////

const FQuaternion FQuaternion::Identity = FQuaternion(0.0f, 0.0f, 0.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
FQuaternion::FQuaternion(void)
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	W = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param x : X
///@param y : Y
///@param z : Z
///@param w : W
//////////////////////////////////////////////////////////////////////////
FQuaternion::FQuaternion(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param vectorPart : ����(XYZ)
///@param scalarPart : ��(W)
//////////////////////////////////////////////////////////////////////////
FQuaternion::FQuaternion(FVector vectorPart, float scalarPart)
{
	X = vectorPart.X;
	Y = vectorPart.Y;
	Z = vectorPart.Z;
	W = scalarPart;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief float*
///@return ��� ������
//////////////////////////////////////////////////////////////////////////
FQuaternion::operator float* ()
{
	return Q;
}

FQuaternion::operator const float* ()
{
	return Q;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator-(void)
{
	FQuaternion quaternion1;
	quaternion1.X = -X;
	quaternion1.Y = -Y;
	quaternion1.Z = -Z;
	quaternion1.W = -W;

	return quaternion1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool FQuaternion::operator==(const FQuaternion& quaternion2) const
{
	if (X == quaternion2.X && Y == quaternion2.Y && Z == quaternion2.Z)
		return W == quaternion2.W;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool FQuaternion::operator!=(const FQuaternion& quaternion2) const
{
	if (X == quaternion2.X && Y == quaternion2.Y && Z == quaternion2.Z)
		return W != quaternion2.W;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator+(const FQuaternion& quaternion2) const
{
	FQuaternion quaternion;
	quaternion.X = X + quaternion2.X;
	quaternion.Y = Y + quaternion2.Y;
	quaternion.Z = Z + quaternion2.Z;
	quaternion.W = W + quaternion2.W;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator-(const FQuaternion& quaternion2) const
{
	FQuaternion quaternion;
	quaternion.X = X - quaternion2.X;
	quaternion.Y = Y - quaternion2.Y;
	quaternion.Z = Z - quaternion2.Z;
	quaternion.W = W - quaternion2.W;
	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator*(const FQuaternion& quaternion2) const
{
	float value1 = Y * quaternion2.Z - Z * quaternion2.Y;
	float value2 = Z * quaternion2.X - X * quaternion2.Z;
	float value3 = X * quaternion2.Y - Y * quaternion2.X;
	float value4 = X * quaternion2.X + Y * quaternion2.Y + Z * quaternion2.Z;

	FQuaternion quaternion;
	quaternion.X = X * quaternion2.W + quaternion2.X * W + value1;
	quaternion.Y = Y * quaternion2.W + quaternion2.Y * W + value2;
	quaternion.Z = Z * quaternion2.W + quaternion2.Z * W + value3;
	quaternion.W = W * quaternion2.W - value4;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : ��
///@return ���
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator*(const float& scaleFactor) const
{
	FQuaternion quaternion;
	quaternion.X = X * scaleFactor;
	quaternion.Y = Y * scaleFactor;
	quaternion.Z = Z * scaleFactor;
	quaternion.W = W * scaleFactor;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::operator/(const FQuaternion& quaternion2) const
{
	float value1 = 1.0f / quaternion2.X * quaternion2.X + quaternion2.Y * quaternion2.Y + quaternion2.Z * quaternion2.Z + quaternion2.W * quaternion2.W;
	float value2 = -quaternion2.X * value1;
	float value3 = -quaternion2.Y * value1;
	float value4 = -quaternion2.Z * value1;
	float value5 = quaternion2.W * value1;

	float multiple1 = Y * value4 - Z * value3;
	float multiple2 = Z * value2 - X * value4;
	float multiple3 = X * value3 - Y * value2;
	float multiple4 = X * value2 + Y * value3 + Z * value4;

	FQuaternion quaternion;
	quaternion.X = X * value5 + value2 * W + multiple1;
	quaternion.Y = Y * value5 + value3 * W + multiple2;
	quaternion.Z = Z * value5 + value4 * W + multiple3;
	quaternion.W = W * value5 - multiple4;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::operator+=(const FQuaternion& quaternion2)
{
	*this = *this + quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::operator-=(const FQuaternion& quaternion2)
{
	*this = *this - quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::operator*=(const FQuaternion& quaternion2)
{
	*this = *this * quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param scaleFactor : ��
///@return ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::operator*=(const float& scaleFactor)
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param quaternion2 : ���ʹϿ�
///@return ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::operator/=(const FQuaternion& quaternion2)
{
	*this = *this / quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ��� ��ȯ
///@param ���ڿ�
//////////////////////////////////////////////////////////////////////////
std::string FQuaternion::ToString()
{
	std::string temp = "";

	temp += std::to_string(X);
	temp += ",:" + std::to_string(Y);
	temp += ",:" + std::to_string(Z);
	temp += ",:" + std::to_string(W);

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ũ�� ���
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
float FQuaternion::Length()
{
	float x = X * X + Y * Y + Z * Z + W * W;

	return sqrtf(x);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �������� ũ�� ���
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
float FQuaternion::LengthSquared()
{
	return X * X + Y * Y + Z * Z + W * W;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����ȭ
//////////////////////////////////////////////////////////////////////////
void FQuaternion::Normalize()
{
	float x = X * X + Y * Y + Z * Z + W * W;
	float value = 1.0f / sqrtf(x);

	X *= value;
	Y *= value;
	Z *= value;
	W *= value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����ȭ
///@param value : ���ʹϿ�
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Normalize(FQuaternion quaternion)
{
	float value = quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z + quaternion.W * quaternion.W;
	float value1 = 1.0f / sqrtf(value);


	FQuaternion q;
	q.X = quaternion.X * value1;
	q.Y = quaternion.Y * value1;
	q.Z = quaternion.Z * value1;
	q.W = quaternion.W * value1;

	return q;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ʹϿ� �ӷ���
//////////////////////////////////////////////////////////////////////////
void FQuaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ʹϿ� �ӷ���
///@param value : ���ʹϿ�
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Conjugate(FQuaternion value)
{
	FQuaternion quaternion;
	quaternion.X = -value.X;
	quaternion.Y = -value.Y;
	quaternion.Z = -value.Z;
	quaternion.W = value.W;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ���ʹϿ�
///@param quaternion : ���ʹϿ�
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Inverse(FQuaternion quaternion)
{
	float value = quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z + quaternion.W * quaternion.W;
	float value1 = 1.0f / value;

	FQuaternion q;
	q.X = -quaternion.X * value1;
	q.Y = -quaternion.Y * value1;
	q.Z = -quaternion.Z * value1;
	q.W = quaternion.W * value1;

	return q;
}
FQuaternion FQuaternion::Add(FQuaternion quaternion1, FQuaternion quaternion2)
{
	FQuaternion quaternion;
	quaternion.X = quaternion1.X + quaternion2.X;
	quaternion.Y = quaternion1.Y + quaternion2.Y;
	quaternion.Z = quaternion1.Z + quaternion2.Z;
	quaternion.W = quaternion1.W + quaternion2.W;

	return quaternion;
}
FQuaternion FQuaternion::Divide(FQuaternion quaternion1, FQuaternion quaternion2)
{
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;

	float value = quaternion2.X * quaternion2.X + quaternion2.Y * quaternion2.Y + quaternion2.Z * quaternion2.Z + quaternion2.W * quaternion2.W;
	float value1 = 1.0f / value;

	float x1 = -quaternion2.X * value1;
	float y1 = -quaternion2.Y * value1;
	float z1 = -quaternion2.Z * value1;
	float w1 = quaternion2.W * value1;

	float value2 = y * z1 - z * y1;
	float value3 = z * x1 - x * z1;
	float value4 = x * y1 - y * x1;
	float value5 = x * x1 + y * y1 + z * z1;

	FQuaternion quaternion;
	quaternion.X = x * w1 + x1 * w + value2;
	quaternion.Y = y * w1 + y1 * w + value3;
	quaternion.Z = z * w1 + z1 * w + value4;
	quaternion.W = w * w1 - value5;

	return quaternion;
}
FQuaternion FQuaternion::Multiply(FQuaternion quaternion1, FQuaternion quaternion2)
{
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;
	float value = quaternion2.X;
	float y1 = quaternion2.Y;
	float z1 = quaternion2.Z;
	float w1 = quaternion2.W;
	float value1 = y * z1 - z * y1;
	float value2 = z * value - x * z1;
	float value3 = x * y1 - y * value;
	float value4 = x * value + y * y1 + z * z1;

	FQuaternion quaternion;
	quaternion.X = x * w1 + value * w + value1;
	quaternion.Y = y * w1 + y1 * w + value2;
	quaternion.Z = z * w1 + z1 * w + value3;
	quaternion.W = w * w1 - value4;

	return quaternion;
}
FQuaternion FQuaternion::Multiply(FQuaternion quaternion1, float scaleFactor)
{
	FQuaternion quaternion;
	quaternion.X = quaternion1.X * scaleFactor;
	quaternion.Y = quaternion1.Y * scaleFactor;
	quaternion.Z = quaternion1.Z * scaleFactor;
	quaternion.W = quaternion1.W * scaleFactor;

	return quaternion;
}
FQuaternion FQuaternion::Subtract(FQuaternion quaternion1, FQuaternion quaternion2)
{
	FQuaternion quaternion;
	quaternion.X = quaternion1.X - quaternion2.X;
	quaternion.Y = quaternion1.Y - quaternion2.Y;
	quaternion.Z = quaternion1.Z - quaternion2.Z;
	quaternion.W = quaternion1.W - quaternion2.W;

	return quaternion;
}
FQuaternion FQuaternion::Negative(FQuaternion quaternion)
{
	FQuaternion x;
	x.X = -quaternion.X;
	x.Y = -quaternion.Y;
	x.Z = -quaternion.Z;
	x.W = -quaternion.W;

	return x;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��� ������ ���� ȸ���� ���ʹϿ�
///@param axis : �� ����
///@param angle : ����
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::CreateFromAxisAngle(FVector axis, float angle)
{
	float value = angle * 0.5f;
	float value1 = sinf(value);
	float value2 = cosf(value);

	FQuaternion quaternion;
	quaternion.X = axis.X * value1;
	quaternion.Y = axis.Y * value1;
	quaternion.Z = axis.Z * value1;
	quaternion.W = value2;
	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ������ ���� ȸ���� ���ʹϿ�
///@param yaw : Yaw - Y
///@param pitch : Pitch - X
///@param roll : Roll - Z
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	float value = roll * 0.5f;
	float value1 = sinf(value);
	float value2 = cosf(value);

	float value3 = pitch * 0.5f;
	float value4 = sinf(value3);
	float value5 = cosf(value3);

	float value6 = yaw * 0.5f;
	float value7 = sinf(value6);
	float value8 = cosf(value6);

	FQuaternion quaternion;
	quaternion.X = value8 * value4 * value2 + value7 * value5 * value1;
	quaternion.Y = value7 * value5 * value2 - value8 * value4 * value1;
	quaternion.Z = value8 * value5 * value1 - value7 * value4 * value2;
	quaternion.W = value8 * value5 * value2 + value7 * value4 * value1;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ʈ������ ���� ȸ���� ���ʹϿ�
///@param matrix : ��Ʈ����
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::CreateFromRotationMatrix(FMatrix matrix)
{
	float m11 = matrix.M11 + matrix.M22 + matrix.M33;

	FQuaternion q;
	if (m11 > 0.0f)
	{
		float value = sqrtf((m11 + 1.0f));
		q.W = value * 0.5f;
		value = 0.5f / value;

		q.X = (matrix.M23 - matrix.M32) * value;
		q.Y = (matrix.M31 - matrix.M13) * value;
		q.Z = (matrix.M12 - matrix.M21) * value;
	}
	else if (matrix.M11 >= matrix.M22 && matrix.M11 >= matrix.M33)
	{
		float value1 = sqrtf((1.0f + matrix.M11 - matrix.M22 - matrix.M33));
		float value2 = 0.5f / value1;

		q.X = 0.5f * value1;
		q.Y = (matrix.M12 + matrix.M21) * value2;
		q.Z = (matrix.M13 + matrix.M31) * value2;
		q.W = (matrix.M23 - matrix.M32) * value2;
	}
	else if (matrix.M22 <= matrix.M33)
	{
		float value3 = sqrtf((1.0f + matrix.M33 - matrix.M11 - matrix.M22));
		float value4 = 0.5f / value3;

		q.X = (matrix.M31 + matrix.M13) * value4;
		q.Y = (matrix.M32 + matrix.M23) * value4;
		q.Z = 0.5f * value3;
		q.W = (matrix.M12 - matrix.M21) * value4;
	}
	else
	{
		float value5 = sqrtf((1.0f + matrix.M22 - matrix.M11 - matrix.M33));
		float value6 = 0.5f / value5;

		q.X = (matrix.M21 + matrix.M12) * value6;
		q.Y = 0.5f * value5;
		q.Z = (matrix.M32 + matrix.M23) * value6;
		q.W = (matrix.M31 - matrix.M13) * value6;
	}

	return q;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����
///@param quaternion1 : ���ʹϿ�1
///@param quaternion2 : ���ʹϿ�2
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
float FQuaternion::Dot(FQuaternion quaternion1, FQuaternion quaternion2)
{
	return quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���麸��
///@param quaternion1 : ���ʹϿ�1
///@param quaternion2 : ���ʹϿ�2
///@param amount : ������
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Slerp(FQuaternion quaternion1, FQuaternion quaternion2, float amount)
{
	float value;
	float value1;
	float value2 = amount;

	bool flag = false;
	float x = quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
	if (x < 0.0f)
	{
		flag = true;
		x = -x;
	}
	if (x <= 0.999999f)
	{
		float value3 = (float)acos((double)x);
		float value4 = (float)(1 / sin((double)value3));
		value1 = sinf(((1.0f - value2) * value3)) * value4;
		value = (flag ? (float)(-sin((double)(value2 * value3))) * value4 : sinf((value2 * value3)) * value4);
	}
	else
	{
		value1 = 1.0f - value2;
		value = (flag ? -value2 : value2);
	}

	FQuaternion quaternion;
	quaternion.X = value1 * quaternion1.X + value * quaternion2.X;
	quaternion.Y = value1 * quaternion1.Y + value * quaternion2.Y;
	quaternion.Z = value1 * quaternion1.Z + value * quaternion2.Z;
	quaternion.W = value1 * quaternion1.W + value * quaternion2.W;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��������
///@param quaternion1 : ���ʹϿ�1
///@param quaternion2 : ���ʹϿ�2
///@param amount : ������
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Lerp(FQuaternion quaternion1, FQuaternion quaternion2, float amount)
{
	float value = amount;
	float value1 = 1.0f - value;

	FQuaternion q;
	if (quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W < 0.0f)
	{
		q.X = value1 * quaternion1.X - value * quaternion2.X;
		q.Y = value1 * quaternion1.Y - value * quaternion2.Y;
		q.Z = value1 * quaternion1.Z - value * quaternion2.Z;
		q.W = value1 * quaternion1.W - value * quaternion2.W;
	}
	else
	{
		q.X = value1 * quaternion1.X + value * quaternion2.X;
		q.Y = value1 * quaternion1.Y + value * quaternion2.Y;
		q.Z = value1 * quaternion1.Z + value * quaternion2.Z;
		q.W = value1 * quaternion1.W + value * quaternion2.W;
	}


	float q1 = q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W;
	float value2 = 1.0f / sqrtf(q1);

	q.X *= value2;
	q.Y *= value2;
	q.Z *= value2;
	q.W *= value2;

	return q;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������ �ٲپ� ���ϱ�
///@param value1 : ���ʹϿ�1
///@param value2 : ���ʹϿ�2
///@return ��� ���ʹϿ�
//////////////////////////////////////////////////////////////////////////
FQuaternion FQuaternion::Concatenate(FQuaternion quaternion1, FQuaternion quaternion2)
{
	float x = quaternion2.X;
	float y = quaternion2.Y;
	float z = quaternion2.Z;
	float w = quaternion2.W;
	float value = quaternion1.X;

	float y1 = quaternion1.Y;
	float z1 = quaternion1.Z;
	float w1 = quaternion1.W;

	float value1 = y * z1 - z * y1;
	float value2 = z * value - x * z1;
	float value3 = x * y1 - y * value;
	float value4 = x * value + y * y1 + z * z1;

	FQuaternion quaternion;
	quaternion.X = x * w1 + value * w + value1;
	quaternion.Y = y * w1 + y1 * w + value2;
	quaternion.Z = z * w1 + z1 * w + value3;
	quaternion.W = w * w1 - value4;

	return quaternion;
}