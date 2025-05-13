#include "Framework.h"
#include "Context.h"

CContext* CContext::Instance = nullptr;

void CContext::Create()
{
	assert(Instance == nullptr);

	Instance = new CContext();
}

void CContext::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CContext* CContext::Get()
{
	return Instance;
}

CContext::CContext()
{
	View = new CCamera();


	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * 0.25f, width / height, 0.1f, 1000.0f);


	Viewport = new D3D11_VIEWPORT();
	Viewport->TopLeftX = 0;
	Viewport->TopLeftY = 0;
	Viewport->Width = width;
	Viewport->Height = height;
	Viewport->MinDepth = 0;
	Viewport->MaxDepth = 1;
}

CContext::~CContext()
{
	Delete(Viewport);
	Delete(View);
}

void CContext::Tick()
{
	Tick_View();
	Tick_WorldTime();
	Tick_Light();
}

void CContext::Tick_View()
{
	if (CMouse::Get()->Press(EMouseButton::Right))
	{
		FVector Position = View->GetPosition();
		if (CKeyboard::Get()->Press('W'))
			Position = Position + View->GetForward() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();
		else if (CKeyboard::Get()->Press('S'))
			Position = Position - View->GetForward() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();

		if (CKeyboard::Get()->Press('D'))
			Position = Position + View->GetRight() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();
		else if (CKeyboard::Get()->Press('A'))
			Position = Position - View->GetRight() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();

		if (CKeyboard::Get()->Press('E'))
			Position = Position + View->GetUp() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();
		else if (CKeyboard::Get()->Press('Q'))
			Position = Position - View->GetUp() * View->GetMoveSpeed() * CTimer::Get()->GetDeltaTime();

		View->SetPosition(Position);


		FVector delta = CMouse::Get()->GetMoveDelta();

		FVector Rotation = View->GetRotation();
		Rotation.X = Rotation.X + delta.Y * View->GetRotationSpeed() * CTimer::Get()->GetDeltaTime();
		Rotation.Y = Rotation.Y + delta.X * View->GetRotationSpeed() * CTimer::Get()->GetDeltaTime();
		Rotation.Z = 0.0f;

		View->SetRotation(Rotation);
	}

	View->Tick();
}

void CContext::Tick_WorldTime()
{
	//ImGui::Separator();
	//ImGui::SeparatorText("Context");
	//ImGui::SliderFloat3("LightDirection", LightDirection, -1, +1);


	if (CKeyboard::Get()->Press(VK_ADD))
		CTimer::Get()->AddWorldTime(*CTimer::Get()->GetManualTimeSpeed());

	if (CKeyboard::Get()->Press(VK_SUBTRACT))
		CTimer::Get()->AddWorldTime(*CTimer::Get()->GetManualTimeSpeed() * -1.0f);


	LightAngle = CTimer::Get()->GetLightAngle();
	FMatrix lightY = FMatrix::CreateRotationY(LightAngle);
	FMatrix lightX = FMatrix::CreateRotationX(FMath::ToRadians(45.0f));
	FMatrix lightTransform = lightX * lightY;

	LightDirection = FVector::TransformCoord(FVector::Forward, lightTransform);


	//LightAngle = 0일때 실제 태양은 지평선 아래에 있음을 보정
	float HorizonRise = FMath::ToRadians(5.0f);
	LightDirection.Z = FMath::Clamp(LightDirection.Z + HorizonRise, -1.0f, 1.0f);

	SunAngle = LightAngle + FMath::ToRadians(90.0f);
	LightIntensity = FMath::Clamp<float>(LightDirection.Z, 0.0f, 1.0f) + 0.5f;


	CheckTrue(bHideSetting);

	int hours = CTimer::Get()->GetHours();
	int minutes = CTimer::Get()->GetMinutes();

	ImGui::Checkbox("Auto World Time", CTimer::Get()->GetAutoWorldTime());
	ImGui::InputFloat("Manual Time Speed", CTimer::Get()->GetManualTimeSpeed(), 5.0f);
	ImGui::InputFloat("Auto Time Speed", CTimer::Get()->GetDayTimeSpeed(), 10.0f);

	ImGui::Separator();
	ImGui::LabelText("DayTime", "%02d: %02d", hours, minutes);
	ImGui::LabelText("LightAngle", "%.3f", LightAngle);
	ImGui::LabelText("SunAngle", "%.3f", SunAngle);
	ImGui::LabelText("LightDirection.Z", "%.3f", LightDirection.Z);
}

void CContext::Tick_Light()
{
	ImGui::Separator();
	ImGui::ColorEdit3("Ambient Global", Ambient);
	ImGui::ColorEdit3("Specular Global", Specular);
	ImGui::InputFloat("Shininess  Global", &Specular.A, 0.01f);
	Specular.A = FMath::Clamp<float>(Specular.A, 0.01f, 10.0f);
}

void CContext::Render()
{
	CD3D::Get()->GetDeviceContext()->RSSetViewports(1, Viewport);

	string str = string("FrameRate : ") + to_string((int)ImGui::GetIO().Framerate);
	CGui::Get()->RenderText(5, 5, 1, 1, 1, str);

	str = CString::Format("Running Time : %0.6f", CTimer::Get()->GetRunningTime());
	CGui::Get()->RenderText(5, 20, 1, 1, 1, str);

	
	FVector rotation = View->GetRotation();
	FVector position = View->GetPosition();

	str = CString::Format("View Rotation : %3.0f, %3.0f, %3.0f", rotation.X, rotation.Y, rotation.Z);
	CGui::Get()->RenderText(5, 35, 1, 1, 1, str);

	str = CString::Format("View Position : %3.2f, %3.2f, %3.2f", position.X, position.Y, position.Z);
	CGui::Get()->RenderText(5, 50, 1, 1, 1, str);
}

void CContext::ResizeScreen()
{
	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * 0.25f, width / height, 0.1f, 1000.0f);


	Viewport->TopLeftX = 0;
	Viewport->TopLeftY = 0;
	Viewport->Width = width;
	Viewport->Height = height;
	Viewport->MinDepth = 0;
	Viewport->MaxDepth = 1;
}

FMatrix CContext::GetViewMatrix()
{
	return View->GetViewMatrix();
}

FMatrix CContext::GetProjectionMatrix()
{
	return Projection;
}
