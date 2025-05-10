#pragma once

#include <Windows.h>
#include <assert.h>

#include <string>
#include <vector>
using namespace std; 


//DirectX
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")



typedef D3DXCOLOR Color;

#include "Definitions.h"
#include "Systems/D3D.h"
#include "Systems/Window.h"