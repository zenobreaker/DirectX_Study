#include "Framework.h"
#include "Mouse.h"

CMouse* CMouse::Instance = nullptr;

void CMouse::Create()
{
	assert(Instance == nullptr);

	Instance = new CMouse();
}

void CMouse::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CMouse* CMouse::Get()
{
	return Instance;
}

bool CMouse::Down(int InType)
{
	return Down((EMouseButton)InType);
}

bool CMouse::Up(int InType)
{
	return Up((EMouseButton)InType);
}

bool CMouse::Press(int InType)
{
	return Press((EMouseButton)InType);
}

bool CMouse::Down(EMouseButton InType)
{
	return ButtonMaps[(int)InType] == EMouseButtonState::Down;
}

bool CMouse::Up(EMouseButton InType)
{
	return ButtonMaps[(int)InType] == EMouseButtonState::Up;
}

bool CMouse::Press(EMouseButton InType)
{
	return ButtonMaps[(int)InType] == EMouseButtonState::Press;
}

void CMouse::Tick()
{
	memcpy(ButtonOldStatus, ButtonStatus, sizeof(BYTE) * (int)EMouseButton::Max);

	ZeroMemory(ButtonStatus, sizeof(BYTE) * (int)EMouseButton::Max);
	ZeroMemory(ButtonMaps, sizeof(EMouseButtonState) * (int)EMouseButton::Max);

	ButtonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	ButtonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	ButtonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (int i = 0; i < (int)EMouseButton::Max; i++)
	{
		int status = ButtonStatus[i];
		int oldStatus = ButtonOldStatus[i];
		
		if (oldStatus == 0 && status == 1)
			ButtonMaps[i] = EMouseButtonState::Down;
		else if (oldStatus == 1 && status == 0)
			ButtonMaps[i] = EMouseButtonState::Up;
		else if (oldStatus == 1 && status == 1)
			ButtonMaps[i] = EMouseButtonState::Press;
		else
			ButtonMaps[i] = EMouseButtonState::None;
	}


	POINT point;
	GetCursorPos(&point);
	ScreenToClient(CD3D::GetDesc().Handle, &point);

	WheelOldStatus.X = WheelStatus.X;
	WheelOldStatus.Y = WheelStatus.Y;

	WheelStatus.X = (float)point.x;
	WheelStatus.Y = (float)point.y;

	WheelMoveDelta = WheelStatus - WheelOldStatus;
	WheelOldStatus.Z = WheelStatus.Z;
}

void CMouse::WndProc(UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
	if (InMessage == WM_MOUSEMOVE)
	{
		Position.X = (float)LOWORD(InlParam);
		Position.Y = (float)HIWORD(InlParam);
	}

	if (InMessage == WM_MOUSEWHEEL)
	{
		WheelOldStatus.Z = WheelStatus.Z;
		WheelStatus.Z += (float)((short)HIWORD(InwParam));
	}
}

CMouse::CMouse()
{
	Position = FVector(0, 0, 0);

	ZeroMemory(ButtonStatus, sizeof(BYTE) * (int)EMouseButton::Max);
	ZeroMemory(ButtonOldStatus, sizeof(BYTE) * (int)EMouseButton::Max);
	ZeroMemory(ButtonMaps, sizeof(EMouseButtonState) * (int)EMouseButton::Max);


	WheelStatus = FVector(0, 0, 0);
	WheelOldStatus = FVector(0, 0, 0);
	WheelMoveDelta = FVector(0, 0, 0);
}

CMouse::~CMouse()
{
}
