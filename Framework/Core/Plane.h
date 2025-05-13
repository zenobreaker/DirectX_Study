#pragma once

class FVector4;
class FMatrix;
class FQuaternion;

//////////////////////////////////////////////////////////////////////////
///@brief ���
//////////////////////////////////////////////////////////////////////////
class FPlane
{
public:
	FPlane(void);
	FPlane(float a, float b, float c, float d);
	FPlane(FVector& normal, float d);
	FPlane(FVector4& value);
	FPlane(FVector& point1, FVector& point2, FVector& point3);


	operator float* ();
	operator const float* ();

	bool operator ==(const FPlane& value) const;
	bool operator !=(const FPlane& value) const;

	std::string ToString();
	

	float Dot(FVector4& value);
	float DotCoordinate(FVector& value);
	float DotNormal(FVector& value);

	void Normalize();
	static FPlane Normalize(FPlane& value);
	static FPlane Transform(FPlane& plane, FMatrix& matrix);
	static FPlane Transform(FPlane& plane, FQuaternion& rotation);

public:
	union
	{
		struct
		{
			FVector Normal;///< ��� ����
			float D;///< �������κ����� �Ÿ�
		};

		float P[4];
	};
	
};