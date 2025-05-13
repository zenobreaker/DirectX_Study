#pragma once

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Tick();

public:
	const FVector& GetPosition();
	void SetPosition(float x, float y, float z);
	void SetPosition(const FVector& InPosition);

	FVector GetRotation();
	void SetRotation(float x, float y, float z);
	void SetRotation(const FVector& InRotation);

	FVector GetForward() { return Forward; }
	FVector GetUp() { return Up; }
	FVector GetRight() { return Right; }

	FMatrix& GetViewMatrix() { return ViewMatrix; }


	float GetMoveSpeed() { return MoveSpeed; }
	float GetRotationSpeed() { return RotationSpeed; }

public:
	void SetMoveSpeed(float InValue) { MoveSpeed = InValue; }
	void SetRotationSpeed(float InValue) { RotationSpeed = InValue; }

private:
	void SetViewMatrix();
	void SetRotationMatrix();

private:
	FVector Position = FVector(0, 0, 0);
	FVector Rotation = FVector(0, 0, 0);

	FVector Forward = FVector(0, 0, 1);
	FVector Up = FVector(0, 1, 0);
	FVector Right = FVector(1, 0, 0);

private:
	float MoveSpeed = 20;
	float RotationSpeed = 100;

private:
	FMatrix ViewMatrix;
	FMatrix RotationMatrix;
};