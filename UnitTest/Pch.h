#pragma once
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "Framework.h"
#pragma comment(lib, "Framework.lib")

#define Push_Main(x) Push(new x())