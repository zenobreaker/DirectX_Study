#include <Windows.h>

#include <d3dx10math.h>

#include <string>
using namespace std; 

struct FD3DDesc
{
	wstring AppName;
	HINSTANCE Instance; 
	HWND Handle; 

	float Width; 
	float Height; 
	bool bVSync;

	D3DXCOLOR Background;
};


int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int command)
{
	FD3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = InInstance;
	desc.Handle = nullptr;

	desc.Width = 1600; 
	desc.Height = 900; 
	desc.bVSync = false; 

	desc.Background = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

	
}