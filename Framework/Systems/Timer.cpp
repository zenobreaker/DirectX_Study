#include "Framework.h"
#include "Timer.h"

CTimer* CTimer::Instance = nullptr;

void CTimer::Create()
{
	assert(Instance == nullptr);

	Instance = new CTimer();
}

void CTimer::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CTimer* CTimer::Get()
{
	return Instance;
}

void CTimer::AddWorldTime(float InValue)
{
	WorldTime += (InValue * 60.0f);

	if (WorldTime < -43200.0f * 1000.0f) //00:00
		WorldTime = -43200.0f * 1000.0f;
}

void CTimer::Tick()
{
	steady_clock::time_point current = steady_clock::now();

	duration<double> temp = current - PrevFrameTime;
	DeltaTime = (float)temp.count();

	PrevFrameTime = current;

	
	duration<float> temp2 = current - StartTime;
	RunningTime = temp2.count();

	
	float msPerDay = SecondsPerDay * 1000.0f;
	float timeSpeed = bAutoWorldTime ? (DeltaTime * 1000.0f * DayTimeSpeed) : 0.0f;
	
	WorldTime = fmodf(WorldTime + timeSpeed, msPerDay);

	//ImGui::Text("World Time : %f", WorldTime);


	LightAngle = (WorldTime / msPerDay) * FMath::TwoPi;


	//���� �� �ð� ��ȯ (0~360�� �� 0~24h)
	float adjustAngle = LightAngle + FMath::Pi; //0->180(PI)
	float totalHours = fmodf((adjustAngle / FMath::TwoPi) * 24.0f, 24.0f);

	//��/�� ���
	Hours = (int)floor(totalHours);
	float tempHour = totalHours - Hours;

	Minutes = (int)round(tempHour * 60.0f) % 60;
	if (Minutes == 60)
	{
		Minutes = 0;
		Hours = (Hours + 1) % 24;
	}
}

CTimer::CTimer()
{
	StartTime = steady_clock::now();
	PrevFrameTime = steady_clock::now();
}

CTimer::~CTimer()
{
	
}
