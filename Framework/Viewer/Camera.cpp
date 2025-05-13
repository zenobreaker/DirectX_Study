#include "Framework.h"
#include "Camera.h"

CCamera::CCamera()
{
	RotationMatrix = FMatrix::Identity;
	ViewMatrix = FMatrix::Identity;


	SetRotationMatrix();
	SetViewMatrix();
}

CCamera::~CCamera()
{
}

void CCamera::Tick()
{

}

const FVector& CCamera::GetPosition()
{
	return Position;
}

void CCamera::SetPosition(float x, float y, float z)
{
	SetPosition(FVector(x, y, z));
}

void CCamera::SetPosition(const FVector& InPosition)
{
	Position = InPosition;

	SetViewMatrix();
}

FVector CCamera::GetRotation()
{
	FVector r;
	r.X = FMath::ToDegrees(Rotation.X);
	r.Y = FMath::ToDegrees(Rotation.Y);
	r.Z = FMath::ToDegrees(Rotation.Z);

	return r;
}

void CCamera::SetRotation(float x, float y, float z)
{
	SetRotation(FVector(x, y, z));
}

void CCamera::SetRotation(const FVector& InRotation)
{
	Rotation.X = FMath::ToRadians(InRotation.X);
	Rotation.Y = FMath::ToRadians(InRotation.Y);
	Rotation.Z = FMath::ToRadians(InRotation.Z);

	SetRotationMatrix();
	SetViewMatrix();
}

void CCamera::SetViewMatrix()
{
	ViewMatrix = FMatrix::CreateLookAt(Position, (Position + Forward), Up);
}

void CCamera::SetRotationMatrix()
{
	FMatrix x, y, z;
	x = FMatrix::CreateRotationX(Rotation.X);
	y = FMatrix::CreateRotationY(Rotation.Y);
	z = FMatrix::CreateRotationZ(Rotation.Z);

	RotationMatrix = x * y * z;


	Forward = FVector::TransformNormal(FVector::Forward, RotationMatrix);
	Up = FVector::TransformNormal(FVector::Up, RotationMatrix);
	Right = FVector::TransformNormal(FVector::Right, RotationMatrix);
}
