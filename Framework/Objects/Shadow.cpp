#include "Framework.h"
#include "Shadow.h"

CShadow::CShadow(FVector InPosition, float InRadius, UINT InWidth, UINT InHeight)
	: Position(InPosition), Radius(InRadius), Width(InWidth), Height(InHeight)
{
	Target = new CRenderTarget(Width, Height);
	Depth = new CDepthStencil(Width, Height);
	Vp = new CViewport(Width, Height);
}

CShadow::~CShadow()
{
	Delete(Target);
	Delete(Depth);
	Delete(Vp);
}

void CShadow::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Shadow");
	ImGui::SliderFloat("Shadow Bias", &Bias, -0.0001f, +0.1f);
	
	//ImGui::InputInt("Shadow Quality", (int*)&Quality, 0);
	ImGui::InputFloat("Shadow Radius", &Radius, 1);

	CalcViewProjection();
}

void CShadow::PreRedner()
{
	FColor color = FColor::Green;
	Target->OMSetRenderTarget(Depth);
	Target->ClearRenderTarget(&color);
	Depth->ClearDepthStencil();
	Vp->RSSetViewport();
}

void CShadow::CalcViewProjection()
{
	FVector direction = CContext::Get()->GetLightDirection();
	FVector position = direction * Radius * -2.0f; 

	View = FMatrix::CreateLookAt(position, Position, FVector::Up);
	printf("Shadow View row0: %f %f %f %f\n", View.M11, View.M12, View.M13, View.M14);
	printf("Shadow View row3: %f %f %f %f\n", View.M41, View.M42, View.M43, View.M44);
	FVector origin;
	origin = FVector::TransformCoord(Position, View);
	
	float l = origin.X - Radius; 
	float b = origin.Y - Radius;
	float n = origin.Z - Radius;

	float r = origin.X + Radius;
	float t = origin.Y + Radius;
	float f = origin.Z + Radius;

	Projection = FMatrix::CreateOrthographic(r - l, t - b, n, f);
}
