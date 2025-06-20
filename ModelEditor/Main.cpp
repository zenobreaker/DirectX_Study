#include "Pch.h"
#include "Main.h"
#include "Systems/Window.h"

#include "Converter.h"

void CMain::Initialize()
{
	//Cube();
	//Sphere();
	//Cone();
	//Cylinder();
	//Plane();

	//Airplane();

	//Kachujin_Old();
	//Kachujin();

	Turtle();

	MessageBox(CD3D::GetDesc().Handle, L"변환 완료", L"Message", MB_OK);
}

void CMain::Cube()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Cube.fbx", 0.1f);
	converter->ExportMaterial(L"Cube");
	converter->ExportMesh(L"Cube");
	Delete(converter);
}

void CMain::Sphere()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Sphere.fbx", 0.1f);
	converter->ExportMaterial(L"Sphere");
	converter->ExportMesh(L"Sphere");
	Delete(converter);
}


void CMain::Cone()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Cone.fbx", 0.1f);
	converter->ExportMaterial(L"Cone");
	converter->ExportMesh(L"Cone");
	Delete(converter);
}

void CMain::Cylinder()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Cylinder.fbx", 0.1f);
	converter->ExportMaterial(L"Cylinder");
	converter->ExportMesh(L"Cylinder");
	Delete(converter);
}

void CMain::Plane()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Plane.fbx", 0.1f);
	converter->ExportMaterial(L"Plane");
	converter->ExportMesh(L"Plane");
	Delete(converter);
}

void CMain::Airplane()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Airplane/Airplane.fbx", 0.01f);
	converter->ExportMaterial(L"Airplane/Airplane");
	converter->ExportMesh(L"Airplane/Airplane");
	Delete(converter);
}

void CMain::Kachujin_Old()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Kachujin_Old/Kachujin.fbx", 0.1f);
	converter->ExportMaterial(L"Kachujin_Old/Kachujin_Old");
	converter->ExportMesh(L"Kachujin_Old/Kachujin_Old");
	Delete(converter);

	converter = new CConverter();
	converter->ReadFile(L"Kachujin_Old/Idle.fbx", 0.1f);
	converter->ExportAnimation(L"Kachujin_Old/Idle");
	Delete(converter);

	converter = new CConverter();
	converter->ReadFile(L"Kachujin_Old/Walk.fbx", 0.1f);
	converter->ExportAnimation(L"Kachujin_Old/Walk");
	Delete(converter);

	converter = new CConverter();
	converter->ReadFile(L"Kachujin_Old/Run.fbx", 0.1f);
	converter->ExportAnimation(L"Kachujin_Old/Run");
	Delete(converter);

	converter = new CConverter();
	converter->ReadFile(L"Kachujin_Old/Salsa.fbx", 0.1f);
	converter->ExportAnimation(L"Kachujin_Old/Salsa");
	Delete(converter);
}

void CMain::Kachujin()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Kachujin/Kachujin.fbx", 0.1f);
	converter->ExportMaterial(L"Kachujin/Kachujin");
	converter->ExportMesh(L"Kachujin/Kachujin");
	Delete(converter);

	converter = new CConverter();
	converter->ReadFile(L"Kachujin/Idle.fbx", 0.1f);
	converter->ExportAnimation(L"Kachujin/Idle");
	Delete(converter);
}

void CMain::Turtle()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Turtle/Turtle.fbx", 0.1f);
	converter->ExportMaterial(L"Turtle/Turtle");
	converter->ExportMesh(L"Turtle/Turtle");
	converter->ExportInnerAnimation(L"Turtle");

	Delete(converter);
}

///////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int command)
{
	FD3DDesc desc;
	desc.AppName = L"Model Editor";
	desc.Instance = InInstance;
	desc.Handle = nullptr;

	desc.Width = 1024;
	desc.Height = 768;

	desc.Background = FColor(0.3f, 0.3f, 0.3f, 1.0f);

	CD3D::SetDesc(desc);


	CMain* main = new CMain();
	WPARAM wParam = CWindow::Run(main, false);
	Delete(main);

	return wParam;
}