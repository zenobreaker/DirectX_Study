#include "Framework.h"
#include "Vector.h"

//////////////////////////////////////////////////////////////////////////

const FVector FVector::Zero = FVector(0.0f, 0.0f, 0.0f);
const FVector FVector::One = FVector(1.0f, 1.0f, 1.0f);

const FVector FVector::UnitX = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::UnitY = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::UnitZ = FVector(0.0f, 0.0f, 1.0f);

const FVector FVector::Up = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::Down = FVector(0.0f, -1.0f, 0.0f);
const FVector FVector::Right = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::Left = FVector(-1.0f, 0.0f, 0.0f);
const FVector FVector::Forward = FVector(0.0f, 0.0f, 1.0f);
const FVector FVector::Backward = FVector(0.0f, 0.0f, -1.0f);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
//////////////////////////////////////////////////////////////////////////
FVector::FVector(void)
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param X = Y = Z = value
//////////////////////////////////////////////////////////////////////////
FVector::FVector(float value)
{
	X = Y = Z = value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param x : X
///@param y : Y
///@param z : Z
//////////////////////////////////////////////////////////////////////////
FVector::FVector(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

FVector::operator float* ()
{
	return V;
}

FVector::operator const float* ()
{
	return V;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator-(void)
{
	FVector vector3;
	vector3.X = -X;
	vector3.Y = -Y;
	vector3.Z = -Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool FVector::operator==(const FVector& value2) const
{
	if (X == value2.X && Y == value2.Y)
		return Z == value2.Z;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool FVector::operator!=(const FVector& value2) const
{
	if (X == value2.X && Y == value2.Y)
		return Z != value2.Z;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator+(const FVector& value2) const
{
	FVector vector3;
	vector3.X = X + value2.X;
	vector3.Y = Y + value2.Y;
	vector3.Z = Z + value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator-(const FVector& value2) const
{
	FVector vector3;
	vector3.X = X - value2.X;
	vector3.Y = Y - value2.Y;
	vector3.Z = Z - value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator*(const FVector& value2) const
{
	FVector vector3;
	vector3.X = X * value2.X;
	vector3.Y = Y * value2.Y;
	vector3.Z = Z * value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator*(const float& scaleFactor) const
{
	FVector vector3;
	vector3.X = X * scaleFactor;
	vector3.Y = Y * scaleFactor;
	vector3.Z = Z * scaleFactor;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator/(const FVector& value2) const
{
	FVector vector3;
	vector3.X = X / value2.X;
	vector3.Y = Y / value2.Y;
	vector3.Z = Z / value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::operator/(const float& divider) const
{
	float num = 1.0f / divider;

	FVector vector3;
	vector3.X = X * num;
	vector3.Y = Y * num;
	vector3.Z = Z * num;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator+=(const FVector& value2)
{
	*this = *this + value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator-=(const FVector& value2)
{
	*this = *this - value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator*=(const FVector& value2)
{
	*this = *this * value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator*=(const float& scaleFactor)
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator/=(const FVector& value2)
{
	*this = *this / value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void FVector::operator/=(const float& divider)
{
	*this = *this / divider;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¹®ÀÚ¿­·Î º¯È¯
///@return ¹®ÀÚ¿­
//////////////////////////////////////////////////////////////////////////
std::string FVector::ToString()
{
	std::string temp = "";
	temp += std::to_string(X);
	temp += "," + std::to_string(Y);
	temp += "," + std::to_string(Z);

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float FVector::Length()
{
	float x = X * X + Y * Y + Z * Z;

	return sqrtf(x);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float FVector::LengthSquared()
{
	return X * X + Y * Y + Z * Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
//////////////////////////////////////////////////////////////////////////
void FVector::Normalize()
{
	float x = X * X + Y * Y + Z * Z;
	float single = 1.0f / sqrtf(x);

	X *= single;
	Y *= single;
	Z *= single;
}

FVector FVector::Add(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X + value2.X;
	vector3.Y = value1.Y + value2.Y;
	vector3.Z = value1.Z + value2.Z;

	return vector3;
}

FVector FVector::Divide(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X / value2.X;
	vector3.Y = value1.Y / value2.Y;
	vector3.Z = value1.Z / value2.Z;

	return vector3;
}

FVector FVector::Divide(FVector value1, float value2)
{
	float single = 1.0f / value2;

	FVector vector3;
	vector3.X = value1.X * single;
	vector3.Y = value1.Y * single;
	vector3.Z = value1.Z * single;

	return vector3;
}

FVector FVector::Multiply(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X * value2.X;
	vector3.Y = value1.Y * value2.Y;
	vector3.Z = value1.Z * value2.Z;

	return vector3;
}

FVector FVector::Multiply(FVector value1, float scaleFactor)
{
	FVector vector3;
	vector3.X = value1.X * scaleFactor;
	vector3.Y = value1.Y * scaleFactor;
	vector3.Z = value1.Z * scaleFactor;

	return vector3;
}

FVector FVector::Subtract(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X - value2.X;
	vector3.Y = value1.Y - value2.Y;
	vector3.Z = value1.Z - value2.Z;

	return vector3;
}

FVector FVector::Negative(FVector value)
{
	FVector vector3;
	vector3.X = -value.X;
	vector3.Y = -value.Y;
	vector3.Z = -value.Z;

	return vector3;
}

FVector FVector::Barycentric(FVector value1, FVector value2, FVector value3, float amount1, float amount2)
{
	FVector vector3;
	vector3.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
	vector3.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
	vector3.Z = value1.Z + amount1 * (value2.Z - value1.Z) + amount2 * (value3.Z - value1.Z);

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float FVector::Distance(FVector value1, FVector value2)
{
	float x = value1.X - value2.X;
	float y = value1.Y - value2.Y;
	float z = value1.Z - value2.Z;
	float single = x * x + y * y + z * z;

	return sqrtf(single);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float FVector::DistanceSquared(FVector value1, FVector value2)
{
	float x = value1.X - value2.X;
	float y = value1.Y - value2.Y;
	float z = value1.Z - value2.Z;

	return x * x + y * y + z * z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ³»Àû °è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float FVector::Dot(FVector value1, FVector value2)
{
	return value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
///@param value : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Normalize(FVector value)
{
	float x = value.X * value.X + value.Y * value.Y + value.Z * value.Z;
	float single = 1.0f / sqrtf(x);

	FVector vector3;
	vector3.X = value.X * single;
	vector3.Y = value.Y * single;
	vector3.Z = value.Z * single;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¿ÜÀû °è»ê
///@param vector1 : º¤ÅÍ1
///@param vector2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Cross(FVector vector1, FVector vector2)
{
	FVector vector3;
	vector3.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
	vector3.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
	vector3.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¹Ý»ç°ª
///@param vector : º¤ÅÍ
///@param normal : ³ë¸Öº¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Reflect(FVector vector, FVector normal)
{
	float x = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;

	FVector vector3;
	vector3.X = vector.X - 2.0f * x * normal.X;
	vector3.Y = vector.Y - 2.0f * x * normal.Y;
	vector3.Z = vector.Z - 2.0f * x * normal.Z;
	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß ÀÛÀº º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Min(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X < value2.X ? value1.X : value2.X;
	vector3.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
	vector3.Z = value1.Z < value2.Z ? value1.Z : value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß Å« º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Max(FVector value1, FVector value2)
{
	FVector vector3;
	vector3.X = value1.X > value2.X ? value1.X : value2.X;
	vector3.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
	vector3.Z = value1.Z > value2.Z ? value1.Z : value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÇØ´ç º¤ÅÍ°¡ ÃÖ¼Ò°ªº¸´Ù ÀÛÀ» °æ¿ì ÃÖ¼Ò°ª, ¹Ý´ëÀÇ °æ¿ì ÃÖ´ë°ª
///@param value1 : º¤ÅÍ
///@param min : ÃÖ¼Ò°ª º¤ÅÍ
///@param max : ÃÖ´ë°ª º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Clamp(FVector value1, FVector min, FVector max)
{
	float x = value1.X;
	x = (x > max.X ? max.X : x);
	x = (x < min.X ? min.X : x);

	float y = value1.Y;
	y = (y > max.Y ? max.Y : y);
	y = (y < min.Y ? min.Y : y);

	float z = value1.Z;
	z = (z > max.Z ? max.Z : z);
	z = (z < min.Z ? min.Z : z);

	FVector vector3;
	vector3.X = x;
	vector3.Y = y;
	vector3.Z = z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍÀÇ ¼±Çüº¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Lerp(FVector value1, FVector value2, float amount)
{
	FVector vector3;
	vector3.X = value1.X + (value2.X - value1.X) * amount;
	vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
	vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ¸¦ ºÎµå·´°Ô º¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::SmoothStep(FVector value1, FVector value2, float amount)
{
	float single;
	if (amount > 1.0f)
		single = 1.0f;
	else
		single = (amount < 0.0f ? 0.0f : amount);


	amount = single;
	amount = amount * amount * (3.0f - 2.0f * amount);

	FVector vector3;
	vector3.X = value1.X + (value2.X - value1.X) * amount;
	vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
	vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Ä«Æ®¹Ä-·Ò º¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param value3 : º¤ÅÍ3
///@param value4 : º¤ÅÍ4
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::CatmullRom(FVector value1, FVector value2, FVector value3, FVector value4, float amount)
{
	float single = amount * amount;
	float single1 = amount * single;

	FVector vector3;
	vector3.X = 0.5f * (2.0f * value2.X + (-value1.X + value3.X) * amount + (2.0f * value1.X - 5.0f * value2.X + 4.0f * value3.X - value4.X) * single + (-value1.X + 3.0f * value2.X - 3.0f * value3.X + value4.X) * single1);
	vector3.Y = 0.5f * (2.0f * value2.Y + (-value1.Y + value3.Y) * amount + (2.0f * value1.Y - 5.0f * value2.Y + 4.0f * value3.Y - value4.Y) * single + (-value1.Y + 3.0f * value2.Y - 3.0f * value3.Y + value4.Y) * single1);
	vector3.Z = 0.5f * (2.0f * value2.Z + (-value1.Z + value3.Z) * amount + (2.0f * value1.Z - 5.0f * value2.Z + 4.0f * value3.Z - value4.Z) * single + (-value1.Z + 3.0f * value2.Z - 3.0f * value3.Z + value4.Z) * single1);

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¿¡¸£¹ÌÆ® º¸°£
///@param value1 : º¤ÅÍ1
///@param tagent1 : º¤ÅÍ1ÀÇ ÅºÁ¨Æ® º¤ÅÍ
///@param value2 : º¤ÅÍ2
///@param tagent2 : º¤ÅÍ2 ÅºÁ¨Æ® º¤ÅÍ
///@param amount : º¸°£°ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Hermite(FVector value1, FVector tangent1, FVector value2, FVector tangent2, float amount)
{
	float single = amount * amount;
	float single1 = amount * single;
	float single2 = 2.0f * single1 - 3.0f * single + 1.0f;
	float single3 = -2.0f * single1 + 3.0f * single;
	float single4 = single1 - 2.0f * single + amount;
	float single5 = single1 - single;

	FVector vector3;
	vector3.X = value1.X * single2 + value2.X * single3 + tangent1.X * single4 + tangent2.X * single5;
	vector3.Y = value1.Y * single2 + value2.Y * single3 + tangent1.Y * single4 + tangent2.Y * single5;
	vector3.Z = value1.Z * single2 + value2.Z * single3 + tangent1.Z * single4 + tangent2.Z * single5;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ º¤ÅÍ º¯È¯
///@param position : º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Transform(FVector position, FMatrix matrix)
{
	float x = position.X * matrix.M11 + position.Y * matrix.M21 + position.Z * matrix.M31 + matrix.M41;
	float single = position.X * matrix.M12 + position.Y * matrix.M22 + position.Z * matrix.M32 + matrix.M42;
	float x1 = position.X * matrix.M13 + position.Y * matrix.M23 + position.Z * matrix.M33 + matrix.M43;

	FVector vector3;
	vector3.X = x;
	vector3.Y = single;
	vector3.Z = x1;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÄõÅÍ´Ï¿Â¿¡ ÀÇÇÑ º¤ÅÍ º¯È¯
///@param value : º¤ÅÍ
///@param rotation : ÄõÅÍ´Ï¿Â
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::Transform(FVector value, FQuaternion rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;
	float w = rotation.W * x;
	float single = rotation.W * y;

	float w1 = rotation.W * z;
	float x1 = rotation.X * x;
	float single1 = rotation.X * y;

	float x2 = rotation.X * z;
	float y1 = rotation.Y * y;
	float y2 = rotation.Y * z;
	float z1 = rotation.Z * z;
	float single2 = value.X * (1.0f - y1 - z1) + value.Y * (single1 - w1) + value.Z * (x2 + single);

	float x3 = value.X * (single1 + w1) + value.Y * (1.0f - x1 - z1) + value.Z * (y2 - w);
	float single3 = value.X * (x2 - single) + value.Y * (y2 + w) + value.Z * (1.0f - x1 - y1);

	FVector vector3;
	vector3.X = single2;
	vector3.Y = x3;
	vector3.Z = single3;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ ³ë¸Öº¤ÅÍ º¯È¯
///@param normal : ¹ý¼± º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::TransformNormal(FVector normal, FMatrix matrix)
{
	float x = normal.X * matrix.M11 + normal.Y * matrix.M21 + normal.Z * matrix.M31;
	float single = normal.X * matrix.M12 + normal.Y * matrix.M22 + normal.Z * matrix.M32;
	float x1 = normal.X * matrix.M13 + normal.Y * matrix.M23 + normal.Z * matrix.M33;

	FVector vector3;
	vector3.X = x;
	vector3.Y = single;
	vector3.Z = x1;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ À§Ä¡(Á¤Á¡)º¤ÅÍ º¯È¯
///@param position : À§Ä¡ º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
FVector FVector::TransformCoord(FVector position, FMatrix matrix)
{
	float single1 = (matrix.M11 * position.X) + (matrix.M21 * position.Y) + (matrix.M31 * position.Z) + matrix.M41;
	float single2 = (matrix.M12 * position.X) + (matrix.M22 * position.Y) + (matrix.M32 * position.Z) + matrix.M42;
	float single3 = (matrix.M13 * position.X) + (matrix.M23 * position.Y) + (matrix.M33 * position.Z) + matrix.M43;
	float single4 = (matrix.M14 * position.X) + (matrix.M24 * position.Y) + (matrix.M34 * position.Z) + matrix.M44;

	return FVector((single1 / single4), (single2 / single4), (single3 / single4));
}