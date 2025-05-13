#include "Framework.h"
#include "Projector.h"

CProjector* CProjector::Instance = nullptr;

void CProjector::Create()
{
	assert(Instance == nullptr);

	Instance = new CProjector();
}

void CProjector::Destroy()
{
	assert(Instance != nullptr);

	Delete(Instance);
}

CProjector* CProjector::Get()
{
	return Instance;
}

CProjector::CProjector()
{
}

CProjector::~CProjector()
{
}

void CProjector::Tick()
{
	ImGui::Separator();
	ImGui::SeparatorText("Projector");
	ImGui::Checkbox("Show Projector Window", &bShowGUI);
	CheckFalse(bShowGUI);


	ImGui::Begin("Projector", &bShowGUI);

	for (UINT i = 0; i < Data.Count; i++)
	{
		FProjector& projector = Projectors[i];

		ImGui::SeparatorText((to_string(i) + "_Projector").c_str());

		ImGui::InputInt((to_string(i) + "_Texture").c_str(), &projector.TextureIndex);
		projector.TextureIndex = FMath::Clamp<int>(projector.TextureIndex, 0, (int)TextureFiles.size() - 1);
		
		ImGui::InputFloat((to_string(i) + "_PositionX").c_str(), &projector.Position.X, 0.1f);
		ImGui::InputFloat((to_string(i) + "_PositionY").c_str(), &projector.Position.Y, 0.1f);
		ImGui::InputFloat((to_string(i) + "_PositionZ").c_str(), &projector.Position.Z, 0.1f);

		ImGui::InputFloat((to_string(i) + "_RotationX").c_str(), &projector.Rotation.X, 0.1f);
		ImGui::InputFloat((to_string(i) + "_RotationY").c_str(), &projector.Rotation.Y, 0.1f);
		ImGui::InputFloat((to_string(i) + "_RotationZ").c_str(), &projector.Rotation.Z, 0.1f);


		ImGui::Separator();

		ImGui::InputFloat((to_string(i) + "_Width").c_str(), &projector.Width, 0.1f);
		ImGui::InputFloat((to_string(i) + "_Height").c_str(), &projector.Height, 0.1f);
		ImGui::InputFloat((to_string(i) + "_Near").c_str(), &projector.Near, 0.1f);
		ImGui::InputFloat((to_string(i) + "_Far").c_str(), &projector.Far, 0.1f);

		ImGui::InputFloat((to_string(i) + "_FOV").c_str(), &projector.FOV, 0.01f);
		

		ImGui::Separator();

		ImGui::ColorEdit3((to_string(i) + "_Color").c_str(), projector.Color);

		projector.ApplyData();
	}

	ImGui::End();
}

void CProjector::AddTexture(wstring InFile)
{
	TextureFiles.push_back(InFile);
}

void CProjector::AddProjector(const FProjector& InData)
{
	assert(Data.Count < MAX_PROJECTOR_COUNT);

	Projectors[Data.Count] = InData;
	Projectors[Data.Count].ProjectorVP = &Data.VPs[Data.Count];

	Projectors[Data.Count].ApplyData();
	
	Data.Count++;
}

void FProjector::ApplyData()
{
	CheckNull(ProjectorVP);

	FProjectorVP* data = ProjectorVP;

	data->TextureIndex = TextureIndex;
	data->Color = Color;

	FMatrix x, y, z;
	x = FMatrix::CreateRotationX(FMath::ToRadians(Rotation.X));
	y = FMatrix::CreateRotationY(FMath::ToRadians(Rotation.Y));
	z = FMatrix::CreateRotationZ(FMath::ToRadians(Rotation.Z));

	FMatrix r = x * y * z;

	FVector position = Position;
	FVector forward = FVector::TransformNormal(FVector::Forward, r);
	FVector up = FVector::TransformNormal(FVector::Up, r);

	data->View = FMatrix::CreateLookAt(position, position + forward, up);


	float w = Width;
	float h = Height;
	float n = Near;
	float f = Far;
	float fov = FOV;
	float aspect = w / h;

	if (FMath::IsZero(FOV) == false)
		data->Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * fov, aspect, n, f);
	else
		data->Projection = FMatrix::CreateOrthographic(w, h, n, f);
}