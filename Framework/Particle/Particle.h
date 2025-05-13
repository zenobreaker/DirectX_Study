#pragma once

class CParticle : public CRenderer
{
public:
	CParticle(wstring InFileName);
	~CParticle();

	void Reset();
	void AddPosition(const FVector& InPosition);

public:
	FParticleData& GetParticleData() { return ParticleData; }

	void SetTexture(wstring InFileName);

public:
	void Tick();
	void Render();

private:
	void ReadFile(wstring InFileName);

	void ReadSettings(const Json::Value& value);
	void ReadVelocity(const Json::Value& value);
	void ReadSpeed(const Json::Value& value);
	void ReadSize(const Json::Value& value);
	void ReadColor(const Json::Value& value);

private:
	void MapVertices();
	void Activate();
	void Deactivate();

private:
	struct FVertexParticle
	{
		FVector Position;
		FVector Velocity;
		FVector4 Random; //x:주기, y:크기, z:회전, w:색상
		float Time;
	};

private:
	struct FDesc
	{
		FColor MinColor;
		FColor MaxColor;

		FVector Gravity;
		float EndVelocity;

		FVector2D StartSize;
		FVector2D EndSize;

		FVector2D RotateSpeed;

		float ReadyTime;
		float ReadyRandomTime;

		float ColorAmount;
		float CurrentTime;
		float Padding[2];
	} Data;
	CConstantBuffer* CBuffer;

private:
	FParticleData ParticleData;
	
	CTexture* Texture = nullptr;
	FVertexParticle* Vertices = nullptr;

	
	float CurrentTime = 0.0f;
	float LastAddTime = 0.0f;

	UINT LeadCount = 0;
	UINT GpuCount = 0;
	UINT ActiveCount = 0;
	UINT DeactiveCount = 0;
};