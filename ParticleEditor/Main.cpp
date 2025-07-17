#include "Pch.h"
#include "Main.h"
#include "Systems/Window.h"
#include <fstream>

void CMain::Initialize()
{
	CContext::Get()->SetHideSetting(true);

	CContext::Get()->GetCamera()->SetRotation(FVector(20.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(+1.50f, 5.95f, -11.30f));
	CContext::Get()->GetCamera()->SetMoveSpeed(2.0f);

	Shader = CShaders::Get()->GetShader(L"Model.fx");
	CreateFloor();

	ButtonSize = ImVec2(WindowWidth - 15.5f, 0.0f);
	UpdateParticleFileList();
}

void CMain::Destroy()
{
	Delete(Floor);
	Delete(Particle);
}

void CMain::Tick()
{
	OnGUI();

	if (Floor != nullptr)
		Floor->Tick(); 

	if (Particle != nullptr)
	{
		Particle->AddPosition(FVector::Zero);
		Particle->Tick();
	}
}

void CMain::Render()
{
	if (Floor != nullptr)
		Floor->Render();

	if (Particle != nullptr)
		Particle->Render();
}

void CMain::OnGUI()
{
	float width = CD3D::GetDesc().Width;
	float height = CD3D::GetDesc().Height;

	bool bOpen = true;
	bOpen = ImGui::Begin("Particle", &bOpen);
	ImGui::SetWindowPos(ImVec2(width - WindowWidth, 0));
	ImGui::SetWindowSize(ImVec2(WindowWidth, height));
	{
		if (ImGui::Button("Make Hollow File", ButtonSize))
		{
			FParticleData data;

			SaveParticleFile(L"Particle", data);
		}


		OnGUI_List();

		if (Particle != nullptr)
		{
			OnGUI_Settings();

			ImGui::Separator();
			ImGui::SeparatorText("Save Settings");

			OnGUI_WriteFile();
		}
	}
	ImGui::End();
}

void CMain::OnGUI_List()
{
	ImGui::Separator();
	ImGui::SeparatorText("Particle List");


	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
	for (UINT i = 0; i < ParticleFileList.size(); i++)
	{
		if (ParticleFileList[i] == L"Particle")
			continue;

		if (ParticleFileList[i] == CurrentFile)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
			ImGui::Button(CString::ToString(ParticleFileList[i]).c_str(), ButtonSize);
			ImGui::PopStyleColor(1);

			continue;
		}

		if (ImGui::Button(CString::ToString(ParticleFileList[i]).c_str(), ButtonSize))
		{
			Delete(Particle);

			CurrentFile = ParticleFileList[i];
			Particle = new CParticle(ParticleFileList[i]);

			bLoop = Particle->GetParticleData().bLoop;
			MaxParticles = Particle->GetParticleData().MaxParticle;
		}
	}//for(i)
	ImGui::PopStyleVar();
}

void CMain::OnGUI_Settings()
{
	ImGui::Separator();
	ImGui::SeparatorText("Particle Settings");

	ImGui::Checkbox("Loop", &bLoop);
	ImGui::SameLine();
	ImGui::SliderInt("Max Count", (int*)&MaxParticles, 1, 2000);


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 0.0f, 1.0f));
	if (ImGui::Button("Apply", ButtonSize))
	{
		Particle->GetParticleData().bLoop = bLoop;
		Particle->GetParticleData().MaxParticle = MaxParticles;
		Particle->Reset();
	}
	ImGui::PopStyleColor(1);


	ImGui::Separator();
	ImGui::SeparatorText("Data Setting");

	if (ImGui::Button("Texture File"))
	{
		CPath::OpenFileDialog
		(
			L"", CPath::ImageFilter, L"../../_Textures/Particles",
			bind(&CMain::ReadTextureFile, this, placeholders::_1),
			CD3D::GetDesc().Handle
		);
	}
	ImGui::SameLine();
	ImGui::Text("%s", CString::ToString(Particle->GetParticleData().TextureFile).c_str());


	const char* types[] = { "Opaque", "Additive", "AlphaBlend", "Multiply", "Multiply2X" };
	ImGui::Combo("Blend Type", (int*)&Particle->GetParticleData().Type, types, 5);

	ImGui::SliderFloat("ReadyTime", &Particle->GetParticleData().ReadyTime, 0.1f, 10.0f);
	ImGui::SliderFloat("ReadyRandomTime", &Particle->GetParticleData().ReadyRandomTime, 0.0f, 100.0f);

	ImGui::SliderFloat("StartVelocity", &Particle->GetParticleData().StartVelocity, 0.0f, 10.0f);
	ImGui::SliderFloat("EndVelocity", &Particle->GetParticleData().EndVelocity, -100.0f, 100.0f);

	ImGui::SliderFloat("MinHorizontalVelocity", &Particle->GetParticleData().MinHorizontalVelocity, -100.0f, 100.0f);
	ImGui::SliderFloat("MaxHorizontalVelocity", &Particle->GetParticleData().MaxHorizontalVelocity, -100.0f, 100.0f);

	ImGui::SliderFloat("MinVerticalVelocity", &Particle->GetParticleData().MinVerticalVelocity, -100.0f, 100.0f);
	ImGui::SliderFloat("MaxVerticalVelocity", &Particle->GetParticleData().MaxVerticalVelocity, -100.0f, 100.0f);

	ImGui::SliderFloat3("Gravity", Particle->GetParticleData().Gravity, -100, 100);

	ImGui::SliderFloat("Color Amount", &Particle->GetParticleData().ColorAmount, 0.1f, 5.0f);

	ImGui::ColorEdit4("MinColor", Particle->GetParticleData().MinColor);
	ImGui::ColorEdit4("MaxColor", Particle->GetParticleData().MaxColor);

	ImGui::SliderFloat("MinRotateSpeed", &Particle->GetParticleData().MinRotateSpeed, -10, 10);
	ImGui::SliderFloat("MaxRotateSpeed", &Particle->GetParticleData().MaxRotateSpeed, -10, 10);

	ImGui::SliderFloat("MinStartSize", &Particle->GetParticleData().MinStartSize, 0, 500);
	ImGui::SliderFloat("MaxStartSize", &Particle->GetParticleData().MaxStartSize, 0, 500);

	ImGui::SliderFloat("MinEndSize", &Particle->GetParticleData().MinEndSize, 0, 500);
	ImGui::SliderFloat("MaxEndSize", &Particle->GetParticleData().MaxEndSize, 0, 500);
}

void CMain::OnGUI_WriteFile()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
	if (ImGui::Button("Save File", ImVec2(WindowWidth - 15, 0)))
	{
		CPath::SaveFileDialog
		(
			CurrentFile, CPath::ParticleFilter, L"../../_Textures/Particles",
			bind(&CMain::SaveParticleData, this, placeholders::_1),
			CD3D::GetDesc().Handle
		);
	}
	ImGui::PopStyleColor(1);
}

void CMain::ReadTextureFile(wstring InFileName)
{
	//MessageBox(CD3D::GetDesc().Handle, InFileName.c_str(), L"", MB_OK);

	wstring fileName = InFileName;
	size_t temp = fileName.find(L"_Textures/");
	size_t length = wstring(L"_Textures/").length();

	wstring file = fileName.substr(temp + length);

	Particle->SetTexture(file);
}

void CMain::SaveParticleData(wstring InFileName)
{
	SaveParticleFile(InFileName, Particle->GetParticleData());
}

wstring CMain::SaveParticleFile(wstring InFileName, FParticleData& InData)
{
	Json::Value settings;
	settings["00_BlendType"] = CString::Format("%d", InData.Type);
	settings["01_bLoop"] = CString::Format("%d", InData.bLoop ? 1 : 0);
	settings["02_TextureFile"] = CString::ToString(InData.TextureFile);
	settings["03_MaxParticle"] = CString::Format("%d", InData.MaxParticle);
	settings["04_ReadyTime"] = CString::Format("%f", InData.ReadyTime);
	settings["05_ReadyRandomTime"] = CString::Format("%f", InData.ReadyRandomTime);
	settings["06_Gravity"] = InData.Gravity.ToString();

	Json::Value velocity;
	velocity["00_StartVelocity"] = CString::Format("%f", InData.StartVelocity);
	velocity["01_EndVelocity"] = CString::Format("%f", InData.EndVelocity);
	velocity["02_MinHorizontalVelocity"] = CString::Format("%f", InData.MinHorizontalVelocity);
	velocity["03_MaxHorizontalVelocity"] = CString::Format("%f", InData.MaxHorizontalVelocity);
	velocity["04_MinVerticalVelocity"] = CString::Format("%f", InData.MinVerticalVelocity);
	velocity["05_MaxVerticalVelocity"] = CString::Format("%f", InData.MaxVerticalVelocity);

	Json::Value speed;
	speed["00_MinRotateSpeed"] = CString::Format("%f", InData.MinRotateSpeed);
	speed["01_MaxRotateSpeed"] = CString::Format("%f", InData.MaxRotateSpeed);

	Json::Value size;
	size["00_MinStartSize"] = CString::Format("%f", InData.MinStartSize);
	size["01_MaxStartSize"] = CString::Format("%f", InData.MaxStartSize);
	size["02_MinEndSize"] = CString::Format("%f", InData.MinEndSize);
	size["03_MaxEndSize"] = CString::Format("%f", InData.MaxEndSize);

	Json::Value color;
	color["00_ColorAmount"] = CString::Format("%f", InData.ColorAmount);
	color["01_MinColor"] = InData.MinColor.ToString();
	color["02_MaxColor"] = InData.MaxColor.ToString();


	Json::Value root;
	root["1_Settgins"] = settings;
	root["2_Velocity"] = velocity;
	root["3_Speed"] = speed;
	root["4_Size"] = size;
	root["5_Color"] = color;


	Json::StyledWriter writer;
	string result = writer.write(root);

	wstring folder = L"../../_Textures/Particles/";
	CPath::CreateFolders(folder);

	wstring fileName = CPath::GetFileNameWithoutExtension(InFileName);
	wstring filePath = folder + fileName + L".particle";

	ofstream stream;
	stream.open(filePath);
	stream << result;
	stream.close();

	wstring message = L"";
	message = fileName + L" Saved.";

	MessageBox(CD3D::GetDesc().Handle, message.c_str(), L"Message", MB_OK);

	return fileName;
}

void CMain::UpdateParticleFileList()
{
	ParticleFileList.clear();
	CPath::GetFiles(&ParticleFileList, L"../../_Textures/Particles/", L"*.particle");

	for (wstring& file : ParticleFileList)
		file = CPath::GetFileNameWithoutExtension(file);
}


void CMain::CreateFloor()
{
	Floor = new CMeshRender(Shader);
	Floor->ReadMaterial(L"51/Floor_Particle");
	Floor->ReadMesh(L"Plane");

	CTransform* t = Floor->AddTransform();
	t->SetScale(FVector(20, 1, 20));
	t->UpdateWorld(); 

	CMaterial* material = Floor->GetMaterial("WorldGridMaterial");
	material->SetTiling(FVector2D(5, 5));
}

///////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int command)
{
	FD3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = InInstance;
	desc.Handle = nullptr;

	desc.Width = 1600;
	desc.Height = 900;

	desc.Background = FColor(0.3f, 0.3f, 0.3f, 1.0f);

	CD3D::SetDesc(desc);


	CMain* main = new CMain();
	WPARAM wParam = CWindow::Run(main);
	Delete(main);

	return wParam;
}