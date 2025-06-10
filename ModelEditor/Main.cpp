#include "Pch.h"
#include "Main.h"
#include "Systems/Window.h"

#include "Converter.h"

void CMain::Initialize()
{
	//Airplane();
	Cube(); 

	MessageBox(CD3D::GetDesc().Handle, L"변환 완료", L"Message", MB_OK);
}

void CMain::Cube()
{
	CConverter* converter = new CConverter(); 
	converter->ReadFile(L"Cube.fbx", 0.1f); 
	converter->ExportMaterial(L"Cube/Cube"); 
	converter->ExportMesh(L"Cube");
	Delete(converter); 
}

void CMain::Airplane()
{
	CConverter* converter = new CConverter();
	converter->ReadFile(L"Airplane/Airplane.fbx", 0.01f);
	converter->ExportMaterial(L"Airplane/Airplane");
	converter->ExportMesh(L"Airplane");
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