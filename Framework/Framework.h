#pragma once

#include <Windows.h>
#include <assert.h>

#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <iterator>
using namespace std;
using namespace chrono;


//DirectX
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx11tex.h>
#include <d3dcompiler.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "D3DCompiler.lib")


//Effect
#include "Effect/d3dx11effect.h"
#pragma comment(lib, "Effect/Effects11d.lib")


//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")


//DirectXTex
#include "DirectXTex/DirectXTex.h"
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

//JsonCpp
#include "Jsoncpp/Json.h"
#pragma comment(lib, "Jsoncpp/jsoncpp_static.lib")


#include "Definitions.h"

#include "Core/Vector2D.h"
#include "Core/Vector.h"
#include "Core/Vector4.h"
#include "Core/Quaternion.h"
#include "Core/Matrix.h"
#include "Core/Plane.h"
#include "Core/Point.h"
#include "Core/Color.h"
#include "Core/Math.h"

#include "Systems/D3D.h"
#include "Systems/Gui.h"
#include "Systems/Keyboard.h"
#include "Systems/Timer.h"
#include "Systems/Mouse.h"

#include "Viewer/Camera.h"
#include "Viewer/RenderTarget.h"
#include "Viewer/DepthStencil.h"
#include "Viewer/Viewport.h"

#include "Renders/Shader.h"
#include "Renders/VertexLayout.h"
#include "Renders/Texture.h"
#include "Renders/Context.h"
#include "Renders/Buffers.h"
#include "Renders/Transform.h"
#include "Renders/Frame.h"
#include "Renders/Material.h"
#include "Renders/Renderer.h"
#include "Renders/Lighting.h"
#include "Renders/Render2D.h"
#include "Renders/Projector.h"

#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/BinaryFile.h"

#include "Model/ModelBone.h"
#include "Model/ModelMesh.h"
#include "Model/MeshRender.h"
#include "Model/ModelAnimation.h"
#include "Model/AnimRender.h"

#include "Objects/CubeMap.h"
#include "Objects/Billboard.h"
#include "Objects/DynamicCubeMap.h"

#include "Particle/ParticleData.h"
#include "Particle/Particle.h"

#include "Environment/Terrain.h"
#include "Environment/Sky.h"
#include "Environment/Rain.h"
#include "Environment/Snow.h"
#include "Environment/Sun.h"

#include "PostEffects/PostEffect.h"
#include "PostEffects/Blur.h"
#include "PostEffects/Bloom.h"