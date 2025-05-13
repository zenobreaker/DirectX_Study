#include "Framework.h"
#include "Lighting.h"

CLighting* CLighting::Instance = nullptr;

void CLighting::Create()
{
	assert(Instance == nullptr);

	Instance = new CLighting();
}

void CLighting::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CLighting* CLighting::Get()
{
	return Instance;
}

CLighting::CLighting()
{

}

CLighting::~CLighting()
{

}

void CLighting::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Lighting");
	ImGui::Checkbox("Show Light Window", &bShowGUI);
	CheckFalse(bShowGUI);

	
	ImGui::Begin("Lighting", &bShowGUI);

	ImGui::Separator();
	ImGui::SeparatorText("PointLight");

	for (UINT i = 0; i < PointLightData.Count; i++)
	{
		FPointLight& light = PointLightData.Lights[i];

		ImGui::SeparatorText((to_string(i) + "_PL").c_str());
		ImGui::InputFloat((to_string(i) + "_PositionX_PL").c_str(), &light.Position.X, 1.0f);
		ImGui::InputFloat((to_string(i) + "_PositionY_PL").c_str(), &light.Position.Y, 0.1f);
		ImGui::InputFloat((to_string(i) + "_PositionZ_PL").c_str(), &light.Position.Z, 1.0f);


		ImGui::Separator();

		ImGui::InputFloat((to_string(i) + "_Range_PL").c_str(), &light.Range, 1.0f);
		light.Range = FMath::Clamp<float>(light.Range, 1.0f, 10.0f);

		ImGui::InputFloat((to_string(i) + "Intensity_PL").c_str(), &light.Intensity, 0.001f);
		light.Intensity = FMath::Clamp<float>(light.Intensity, 0.0f, 1.0f);


		ImGui::Separator();

		ImGui::ColorEdit3((to_string(i) + "_Diffuse_PL").c_str(), light.Diffuse);
		ImGui::ColorEdit3((to_string(i) + "_Specular_PL").c_str(), light.Specular);
		ImGui::ColorEdit3((to_string(i) + "Emissive_PL").c_str(), light.Emissive);
	}


	ImGui::SeparatorText("SpotLight");

	for (UINT i = 0; i < SpotLightData.Count; i++)
	{
		FSpotLight& light = SpotLightData.Lights[i];

		ImGui::SeparatorText((to_string(i) + "_SL").c_str());
		ImGui::InputFloat((to_string(i) + "_PositionX_SL").c_str(), &light.Position.X, 1.0f);
		ImGui::InputFloat((to_string(i) + "_PositionY_SL").c_str(), &light.Position.Y, 0.1f);
		ImGui::InputFloat((to_string(i) + "_PositionZ_SL").c_str(), &light.Position.Z, 1.0f);


		ImGui::Separator();

		ImGui::InputFloat((to_string(i) + "_Range_SL").c_str(), &light.Range, 1.0f);
		light.Range = FMath::Clamp<float>(light.Range, 1.0f, 10.0f);

		ImGui::InputFloat((to_string(i) + "_Intensity_SL").c_str(), &light.Intensity, 0.001f);
		light.Intensity = FMath::Clamp<float>(light.Intensity, 0.0f, 1.0f);

		ImGui::InputFloat((to_string(i) + "_Angle_SL").c_str(), &light.Angle, 1.0f);
		light.Angle = FMath::Clamp<float>(light.Angle, 1.0f, 90.0f);

		ImGui::SliderFloat3((to_string(i) + "_Direction_SL").c_str(), light.Direction, -1.0f, +1.0f);

		ImGui::Separator();

		ImGui::ColorEdit3((to_string(i) + "_Diffuse_SL").c_str(), light.Diffuse);
		ImGui::ColorEdit3((to_string(i) + "_Specular_SL").c_str(), light.Specular);
		ImGui::ColorEdit3((to_string(i) + "_Emissive_SL").c_str(), light.Emissive);
	}

	ImGui::End();
}


///////////////////////////////////////////////////////////////////////////////

void CLighting::AddPointLight(const FPointLight& InLight)
{
	assert(PointLightData.Count < MAX_LIGHT_COUNT);

	PointLightData.Lights[PointLightData.Count] = InLight;
	PointLightData.Count++;
}

///////////////////////////////////////////////////////////////////////////////

void CLighting::AddSpotLight(const FSpotLight& InLight)
{
	assert(SpotLightData.Count < MAX_LIGHT_COUNT);

	SpotLightData.Lights[SpotLightData.Count] = InLight;
	SpotLightData.Count++;
}
