#include "Framework.h"
#include "Particle.h"

CParticle::CParticle(wstring InFileName)
	: CRenderer(L"00_Particle.fxo")
{
	InFileName = L"../../_Textures/Particles/" + InFileName + L".particle";
	ReadFile(InFileName);

	CBuffer = new CConstantBuffer(Shader, "CB_Particle", &Data, sizeof(FDesc));

	Reset();
}

CParticle::~CParticle()
{
	Delete(Texture);
	Delete(CBuffer);

	DeleteArray(Vertices);
}

void CParticle::Reset()
{
	CurrentTime = 0.0f;
	LastAddTime = CTimer::Get()->GetRunningTime();

	LeadCount = GpuCount = ActiveCount = DeactiveCount = 0;

	DeleteArray(Vertices);
	Delete(VBuffer);


	Vertices = new FVertexParticle[ParticleData.MaxParticle];
	VBuffer = new CVertexBuffer(Vertices, ParticleData.MaxParticle, sizeof(FVertexParticle), 0, true);
}

void CParticle::AddPosition(const FVector& InPosition)
{
	if (CTimer::Get()->GetRunningTime() - LastAddTime < 60.0f / 1000.0f)
		return;

	LastAddTime = CTimer::Get()->GetRunningTime();


	UINT count = LeadCount + 1;

	if (count >= ParticleData.MaxParticle)
	{
		if (ParticleData.bLoop)
		{
			count = 0;
		}
		else
		{
			count = ParticleData.MaxParticle;

			return;
		}
	}

	CheckTrue(count == DeactiveCount);


	FVector velocity = FVector::One;
	velocity *= ParticleData.StartVelocity;

	float horizontalVelocity = FMath::Lerp(ParticleData.MinHorizontalVelocity, ParticleData.MaxHorizontalVelocity, FMath::Random(0.0f, 1.0f));
	float horizontalAngle = FMath::Pi * 2.0f * FMath::Random(0.0f, 1.0f);

	velocity.X += horizontalVelocity * cosf(horizontalAngle);
	velocity.Y += horizontalVelocity * sinf(horizontalAngle);
	velocity.Z += FMath::Lerp(ParticleData.MinHorizontalVelocity, ParticleData.MaxHorizontalVelocity, FMath::Random(0.0f, 1.0f));


	FVector4 random;
	random.X = FMath::Random(0.0f, 1.0f);
	random.Y = FMath::Random(0.0f, 1.0f);
	random.Z = FMath::Random(0.0f, 1.0f);
	random.W = FMath::Random(0.0f, 1.0f);


	Vertices[LeadCount].Position = InPosition;
	Vertices[LeadCount].Velocity = velocity;
	Vertices[LeadCount].Random = random;
	Vertices[LeadCount].Time = CurrentTime;


	LeadCount = count;
}

void CParticle::SetTexture(wstring InFileName)
{
	Delete(Texture);

	ParticleData.TextureFile = InFileName;
	Texture = new CTexture(Shader, "ParticleMap", InFileName);
}

void CParticle::Tick()
{
	CurrentTime += CTimer::Get()->GetDeltaTime();

	MapVertices();
	Activate();
	Deactivate();

	if (ActiveCount == LeadCount)
		CurrentTime = 0.0f;


	Data.MinColor = ParticleData.MinColor;
	Data.MaxColor = ParticleData.MaxColor;
	Data.ColorAmount = ParticleData.ColorAmount;

	Data.Gravity = ParticleData.Gravity;
	Data.EndVelocity = ParticleData.EndVelocity;

	Data.RotateSpeed = FVector2D(ParticleData.MinRotateSpeed, ParticleData.MaxRotateSpeed);
	Data.StartSize = FVector2D(ParticleData.MinStartSize, ParticleData.MaxStartSize);
	Data.EndSize = FVector2D(ParticleData.MinEndSize, ParticleData.MaxEndSize);

	Data.ReadyTime = ParticleData.ReadyTime;
	Data.ReadyRandomTime = ParticleData.ReadyRandomTime;
	
	Super::Tick();	
}

void CParticle::Render()
{
	Super::Render();

	CBuffer->Render();
	Texture->Render();

	Data.CurrentTime = CurrentTime;
	CheckTrue(LeadCount == ActiveCount);


	IA_POINTLIST();

	UINT pass = (UINT)ParticleData.Type;
	if (LeadCount > ActiveCount)
	{
		Shader->SetPassNumber(pass);
		Shader->Draw(LeadCount - ActiveCount, ActiveCount);
	}
	else
	{
		Shader->SetPassNumber(pass);
		Shader->Draw(ParticleData.MaxParticle - ActiveCount, ActiveCount);

		if (LeadCount > 0)
			Shader->Draw(LeadCount);
	}
}

void CParticle::MapVertices()
{
	CheckTrue(GpuCount == LeadCount);


	D3D11_MAPPED_SUBRESOURCE subResource;

	if (LeadCount > GpuCount)
	{
		CD3D::Get()->GetDeviceContext()->Map(*VBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subResource);
		{
			UINT start = GpuCount;
			UINT size = (LeadCount - GpuCount) * sizeof(FVertexParticle);
			UINT offset = GpuCount * sizeof(FVertexParticle);

			BYTE* p = (BYTE*)subResource.pData + offset;
			memcpy(p, Vertices + start, size);
		}
		CD3D::Get()->GetDeviceContext()->Unmap(*VBuffer, 0);
	}
	else
	{
		CD3D::Get()->GetDeviceContext()->Map(*VBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subResource);
		{
			UINT start = GpuCount;
			UINT size = (ParticleData.MaxParticle - GpuCount) * sizeof(FVertexParticle);
			UINT offset = GpuCount * sizeof(FVertexParticle);

			BYTE* p = (BYTE*)subResource.pData + offset;
			memcpy(p, Vertices + start, size);

			if (LeadCount > 0)
			{
				UINT size = LeadCount * sizeof(FVertexParticle);

				memcpy(subResource.pData, Vertices, size);
			}
		}
		CD3D::Get()->GetDeviceContext()->Unmap(*VBuffer, 0);
	}

	GpuCount = LeadCount;
}

void CParticle::Activate()
{
	while (ActiveCount != GpuCount)
	{
		float age = CurrentTime - Vertices[ActiveCount].Time;

		if (age < Data.ReadyTime)
			return;


		Vertices[ActiveCount].Time = CurrentTime;
		ActiveCount++;

		if (ActiveCount >= ParticleData.MaxParticle)
			ActiveCount = ParticleData.bLoop ? 0 : ParticleData.MaxParticle;
	}
}

void CParticle::Deactivate()
{
	while (ActiveCount != DeactiveCount)
	{
		float age = CurrentTime - Vertices[ActiveCount].Time;

		if (age > Data.ReadyTime)
			return;

		DeactiveCount++;

		if (DeactiveCount >= ParticleData.MaxParticle)
			DeactiveCount = ParticleData.bLoop ? 0 : ParticleData.MaxParticle;
	}
}
