#pragma once
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "Framework.h"
#pragma comment(lib, "Framework.lib")

#include "Assimp/importer.hpp"
#include "Assimp/postprocess.h"
#include "Assimp/scene.h"
#pragma comment(lib, "Assimp/assimp-vc143-mtd.lib")

#define Push_Main(x) Push(new x())