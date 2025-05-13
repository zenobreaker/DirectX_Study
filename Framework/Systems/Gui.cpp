#include "Framework.h"
#include "Gui.h"

CGui* CGui::Instance = nullptr;

void CGui::Create()
{
	assert(Instance == nullptr);

	Instance = new CGui();
}

void CGui::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CGui* CGui::Get()
{
	return Instance;
}

void CGui::Tick()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void CGui::Render()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowBgAlpha(0.0f);


	ImGui::Begin
	(
		"TextWindow", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus
	);

	
	for (FGuiText content : Contents)
	{
		ImVec2 position = ImVec2(content.Position.X, content.Position.Y);
		ImColor color = ImColor(content.Color.R, content.Color.G, content.Color.B, content.Color.A);

		ImGui::GetWindowDrawList()->AddText(position, color, content.Content.c_str());
	}
	Contents.clear();


	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CGui::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
	if (ImGui::GetCurrentContext() == nullptr)
		return 0;

	return ImGui_ImplWin32_WndProcHandler(InHandle, InMessage, InwParam, InlParam);
}

void CGui::RenderText(float x, float y, float r, float g, float b, string content)
{
	RenderText(x, y, r, g, b, 1.0f, content);
}

void CGui::RenderText(float x, float y, float r, float g, float b, float a, string content)
{
	FGuiText text;
	text.Position = FVector2D(x, y);
	text.Color = FColor(r, g, b, a);
	text.Content = content;

	Contents.push_back(text);
}

CGui::CGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	
	const FD3DDesc& desc = CD3D::GetDesc();

	ImGui_ImplWin32_Init(desc.Handle);
	ImGui_ImplDX11_Init(CD3D::Get()->GetDevice(), CD3D::Get()->GetDeviceContext());
}

CGui::~CGui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
