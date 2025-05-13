#pragma once

class CTransform
{
public:
	CTransform(CShader* InShader);
	CTransform(FMatrix* InMatrix);
	~CTransform();

	void Render();

public:
	FVector GetForward();
	FVector GetUp();
	FVector GetRight();

public:
	const FMatrix& GetMatrix() { return BufferData.World; }
	void SetMatrix(const FMatrix& InMatrix) { BufferData.World = InMatrix; }

public:
	const FVector& GetPosition();
	void SetPosition(const FVector& InValue);

	const FVector& GetScale();
	void SetScale(const FVector& InValue);

	FVector GetRotation();
	void SetRotation(const FVector& InValue);

public:
	void UpdateWorld();

private:
	struct BufferDesc
	{
		FMatrix World;
	} BufferData;

private:
	CShader* Shader = nullptr;
	CConstantBuffer* CBuffer = nullptr;

private:
	bool bDirty = false;

private:
	FVector Position = FVector::Zero;
	FVector Scale = FVector::One;
	FVector Rotation = FVector::Zero;

private:
	FMatrix* WorldMatrix = nullptr;
};