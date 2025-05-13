#include "Framework.h"
#include "Transform.h"

CTransform::CTransform(CShader* InShader)
	: Shader(InShader)
{
	BufferData.World = FMatrix::Identity;

	CBuffer = new CConstantBuffer(InShader, "CB_World", &BufferData, sizeof(BufferDesc));
}

CTransform::CTransform(FMatrix* InMatrix)
{
	BufferData.World = FMatrix::Identity;

	WorldMatrix = InMatrix;
}

CTransform::~CTransform()
{
	Delete(CBuffer);
}

void CTransform::Render()
{
	if (bDirty)
	{
		bDirty = false;
		UpdateWorld();
	}

	assert(CBuffer != nullptr);
	CBuffer->Render();
}

FVector CTransform::GetForward()
{
	return BufferData.World.Forward();
}

FVector CTransform::GetUp()
{
	return BufferData.World.Up();
}

FVector CTransform::GetRight()
{
	return BufferData.World.Right();
}

const FVector& CTransform::GetPosition()
{
	return Position;
}

void CTransform::SetPosition(const FVector& InValue)
{
	Position = InValue;

	bDirty = true;
}

const FVector& CTransform::GetScale()
{
	return Scale;
}

void CTransform::SetScale(const FVector& InValue)
{
	Scale = InValue;

	bDirty = true;
}

FVector CTransform::GetRotation()
{
	FVector v;

	v.X = FMath::ToDegrees(Rotation.X);
	v.Y = FMath::ToDegrees(Rotation.Y);
	v.Z = FMath::ToDegrees(Rotation.Z);

	return v;
}

void CTransform::SetRotation(const FVector& InValue)
{
	FVector v;

	v.X = FMath::ToRadians(InValue.X);
	v.Y = FMath::ToRadians(InValue.Y);
	v.Z = FMath::ToRadians(InValue.Z);

	Rotation = v;

	bDirty = true;
}

void CTransform::UpdateWorld()
{
	FMatrix t, r, s;
	t = FMatrix::CreateTranslation(Position);
	s = FMatrix::CreateScale(Scale);
	r = FMatrix::CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z);

	BufferData.World = s * r * t;

	
	if (WorldMatrix != nullptr)
		memcpy(WorldMatrix, &BufferData.World, sizeof(FMatrix));
}

