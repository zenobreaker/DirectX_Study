#include "Pch.h"
#include "Demo.h"

CDemo_MRT::CDemo_MRT(ID3D11ShaderResourceView* InSRV)
	: CRenderer(L"MRT.fxo")
{
	FVertex vertices[4];
	vertices[0].Position = FVector(-1.0f, -1.0f, 0.0f);
	vertices[1].Position = FVector(-1.0f, +1.0f, 0.0f);
	vertices[2].Position = FVector(+1.0f, -1.0f, 0.0f);
	vertices[3].Position = FVector(+1.0f, +1.0f, 0.0f);

	VBuffer = new CVertexBuffer(vertices, 4, sizeof(FVertex));

	Shader->AsSRV("MRTMap")->SetResource(InSRV);
}

CDemo_MRT::~CDemo_MRT()
{
}

void CDemo_MRT::Tick()
{
	Super::Tick();
}

void CDemo_MRT::Render()
{
	Super::Render();

	IA_TRIANGLESTRIP();
	Shader->Draw(4);
}


void CDemo::Initialize()
{
	CContext::Get()->GetCamera()->SetRotation(FVector(30.0f, 0.0f, 0.0f));
	CContext::Get()->GetCamera()->SetPosition(FVector(119.0f, 4.31f, 81.43f));
	CContext::Get()->GetCamera()->SetMoveSpeed(10.0f);


	UINT width = (UINT)CD3D::GetDesc().Width;
	UINT height = (UINT)CD3D::GetDesc().Height;

	MaterialFolder = L"";
	ShaderFile = L"Shadow.fx";

	CreateLighting();
	CreateProjector();

	CreateFloor();
	CreateSky();
	//CreateSphere();

	//CreateKachujin();
	//CreateKachujin_Old();
	CreateTurtle_Anim();

	UINT size = 1024;
	DepthRender = new CRender2D(*CContext::Get()->GetShadow());
	DepthRender->GetTransform()->SetScale(FVector(400, 225, 1));
	DepthRender->GetTransform()->SetPosition(FVector(250, 160, 0));
}

void CDemo::Destroy()
{
	Delete(Render2D);
	Delete(DepthRender);
	Delete(Terrain);
	Delete(Sky);

	for (auto& render : Renders)
		Delete(render);
}

void CDemo::Tick()
{
	//Terrain->Tick(); 
	ImGui::Separator();
	ImGui::SeparatorText("Render Pass");
	static int pass = 0;
	ImGui::SliderInt("Pass", (int*)&pass, 0, 1);

	ImGui::SeparatorText("Model");
	static int prev = 0;
	ImGui::SliderInt("Model", (int*)&ModelIndex, 0, Renders.size() - 1);

	for (auto render : Renders)
	{
		render->SetPass(pass);
		render->Tick();
	}

	if (BoneDebugger != nullptr)
		BoneDebugger->Tick();

	Sky->Tick();

	//switch (WeatherType)
	//{
	//	case EWeatherType::Rain: Rain->Tick(); break;
	//	case EWeatherType::Snow: Snow->Tick(); break;
	//}

	/*Blur->Tick();
	PostEffect->Tick();*/
	DepthRender->SetSRV(*CContext::Get()->GetShadow());
	DepthRender->Tick();
}

void CDemo::PreRender()
{
	ImGui::SliderInt("Pass ", (int*)&Pass, 1, 0);

	//Terrain->SetPass(Pass);
	//Terrain->Render();

	CContext::Get()->GetShadow()->PreRedner(); 

	for (auto render : Renders)
		render->Render();

	if (BoneDebugger != nullptr)
		BoneDebugger->Render();


	//switch (WeatherType)
	//{
	//	case EWeatherType::Rain: Rain->Render(); break;
	//	case EWeatherType::Snow: Snow->Render(); break;
	//}
	//Blur->End_PreRender();
	
	//PostEffect->PreRender(*Bloom->GetRenderTarget());

}

void CDemo::Render()
{
	Sky->Render();

	for (auto render : Renders)
	{
		render->SetPass(2);
		render->Render();
	}

	if (BoneDebugger != nullptr)
		BoneDebugger->Render();
}

void CDemo::PostRender()
{
	DepthRender->Render();
}

void CDemo::CreateTerrain()
{
	Terrain = new CTerrain(L"Terrain/Gray256.png", ShaderFile);
	Terrain->SetBaseMap(L"Terrain/Sand.png", L"Terrain/Sand_Normal.png");
	Terrain->SetLowMap(L"Terrain/Grass.png", L"Terrain/Grass_Normal.png");
	Terrain->SetHighMap(L"Terrain/Grass2.png", L"Terrain/Grass2_Normal.png");
	Terrain->SetSlopeMap(L"Terrain/Rock.png", L"Terrain/Rock_Normal.png");
}

void CDemo::CreateSky()
{
	Sky = new CSky(L"Environments/Sky1024.dds", L"99_Environment.fx", 100.0f);
	//Rain = new CRain(FVector(300, 100, 500), 1e+4f);
	//Snow = new CSnow(FVector(300, 100, 500), 1e+4f);
}

void CDemo::CreateLighting()
{
	FPointLight pointLight;

	FVector position;

	{
		pointLight = FPointLight();
		pointLight.Diffuse = FColor(0.0f, 1.0f, 0.0f, 1.0f);
		pointLight.Specular = FColor(0.0f, 0.7f, 0.0f, 1.0f);
		pointLight.Emissive = FColor(0.0f, 0.7f, 0.0f, 1.0f);
		pointLight.Position = FVector(Position.X, 8.9f, Position.Z);
		position = FVector(Position.X, 8.9f, Position.Z);;
		pointLight.Range = 9.0f;
		pointLight.Intensity = 0.5;

		CLighting::Get()->AddPointLight(pointLight);
	}

	{
		pointLight = FPointLight();
		pointLight.Diffuse = FColor(0.0f, 0.0f, 1.0f, 1.0f);
		pointLight.Specular = FColor(0.0f, 0.0f, 0.7f, 1.0f);
		pointLight.Emissive = FColor(0.0f, 0.0f, 0.7f, 1.0f);
		pointLight.Position = FVector(+1.0f, 0, 0.0f);

		pointLight.Range = 9.0f;
		pointLight.Intensity = 0.5;
		pointLight.Position += position;
		CLighting::Get()->AddPointLight(pointLight);
	}

	{
		pointLight = FPointLight();
		pointLight.Diffuse = FColor(1.0f, 0.0f, 0.0f, 1.0f);
		pointLight.Specular = FColor(0.7f, 0.0f, 0.0f, 1.0f);
		pointLight.Emissive = FColor(0.7f, 0.0f, 0.0f, 1.0f);
		pointLight.Position = FVector(+2.0f, 0, 0.0f);

		pointLight.Range = 9.0f;
		pointLight.Intensity = 0.5;
		pointLight.Position += position;
		CLighting::Get()->AddPointLight(pointLight);
	}

	FSpotLight spotLight;

	//1 - Spot Light
	{
		spotLight = FSpotLight();
		spotLight.Diffuse = FColor(0.7f, 1.0f, 0.0f, 1.0f);
		spotLight.Specular = FColor(0.3f, 1.0f, 0.0f, 1.0f);
		spotLight.Emissive = FColor(0.3f, 1.0f, 0.0f, 1.0f);
		spotLight.Position = FVector(-5.0f, 5.0f, +3.0f);
		spotLight.Range = 30.0f;
		spotLight.Intensity = 0.55f;
		spotLight.Direction = FVector(0, -1, 0);
		spotLight.Angle = 40.0f;

		spotLight.Position += Position;
		CLighting::Get()->AddSpotLight(spotLight);
	}

	//2 - Spot Light
	{
		spotLight = FSpotLight();
		spotLight.Diffuse = FColor(1.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Specular = FColor(1.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Emissive = FColor(1.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Position = FVector(-2.5f, 5.0f, +3.0f);
		spotLight.Range = 30.0f;
		spotLight.Intensity = 0.55f;
		spotLight.Direction = FVector(0, -1, 0);
		spotLight.Angle = 40.0f;

		spotLight.Position += Position;
		CLighting::Get()->AddSpotLight(spotLight);
	}

	//3 - Spot Light
	{
		spotLight = FSpotLight();
		spotLight.Diffuse = FColor(0.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Specular = FColor(0.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Emissive = FColor(0.0f, 0.2f, 0.9f, 1.0f);
		spotLight.Position = FVector(0.0f, 5.0f, +3.0f);
		spotLight.Range = 35.0f;
		spotLight.Intensity = 0.3f;
		spotLight.Direction = FVector(0, -1, 0);
		spotLight.Angle = 20.0f;
		spotLight.Position += Position;
		CLighting::Get()->AddSpotLight(spotLight);
	}

}

void CDemo::CreateProjector()
{
	CProjector::Get()->AddTexture(L"Environments/Window.png");
	CProjector::Get()->AddTexture(L"Environments/MagicCircle.png");


	FProjector projector;

	projector = FProjector();
	projector.TextureIndex = 0;
	projector.Color = FColor::Blue;
	projector.Far = 10;
	projector.FOV = 0.25f;

	projector.Rotation = FVector(90, 0, 0);
	projector.Position = FVector(-6.0f, 7.0f, -6.9f);
	projector.Position += Position;

	CProjector::Get()->AddProjector(projector);


	projector = FProjector();
	projector.TextureIndex = 1;
	projector.Color = FColor::Green;
	projector.Far = 10;
	projector.Width = 3;
	projector.Height = 3;

	//117.5, 5, 87
	projector.Rotation = FVector(-90, 0, 0);
	projector.Position = FVector(-2.5f, 1.0f, -3.0f);
	projector.Position += Position;

	CProjector::Get()->AddProjector(projector);
}

void CDemo::CreateBloom()
{
	Bloom = new CBloom();

	Render2D = new CRender2D(*Bloom->GetRenderTarget());
	Render2D->GetTransform()->SetScale(FVector(400, 225, 1));
	Render2D->GetTransform()->SetPosition(FVector(250, 160, 0));
}


void CDemo::CreateBillboard()
{
	Billboard = new CBillboard(L"Grass.fx");
	Billboard->AddTexture(L"Terrain/Billboard.png");
	Billboard->AddTexture(L"Terrain/Billboard2.png");
	Billboard->AddTexture(L"Terrain/Billboard3.png");


	for (UINT z = 0; z < Terrain->GetHeight(); z += 3)
	{
		for (UINT x = 0; x < Terrain->GetWidth(); x += 3)
		{
			//모델 배치 영역
			if (x >= 105 && x <= 125 && z >= 80 && z <= 95)
				continue;


			UINT index = z * Terrain->GetWidth() + x;

			float height = Terrain->GetY(x, z);
			float probability = 0.0f; //배치 확률

			const FVector4 weights = Terrain->GetWeights(x, z);

			float low = Terrain->GetHeightLowRatio();
			float high = Terrain->GetHeightHighRatio();

			float minY = 0.1f;
			float maxY = (high + low) * 0.75f;


			if (height > minY && height < maxY)
			{
				if (weights.W < 0.6f)
					probability = 1.0f; //경사면
			}//if(height)

			float r = FMath::Random(0.0f, 1.0f);
			if (probability >= r)
			{
				FVector position = FVector::Zero;
				position.X = ((float)x + FMath::Random(0.0f, 2.5f));
				position.Y = height;
				position.Z = ((float)z + FMath::Random(0.0f, 2.5f));

				float randomX = FMath::Random(1.0f, 2.0f);
				float randomY = FMath::Random(3.0f, 6.0f);

				int random = FMath::Random(0, 2);
				Billboard->AddPosition(position, FVector2D(randomX, randomY), random);
			} //if(probability)	
		}
	}
}

void CDemo::CreateCube()
{
	Shader = CShaders::Get()->GetShader(ShaderFile);
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Cube");
	render->AddMaterial(L"Box");
	render->ReadMesh(L"Cube");

	int index = 0;
	for (float x = -7.0f; x <= 7.0; x += 0.1f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, -5.5f, Position.Z - 0.5f));
		float rotX = FMath::Random(0.f, 180.f);
		float rotZ = FMath::Random(0.f, 180.f);
		t->SetRotation(FVector(rotX, 0, rotZ));
		t->UpdateWorld();
	}

	Renders.push_back(render);
}

void CDemo::CreateFloor()
{
	Shader = CShaders::Get()->GetShader(ShaderFile);
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Plane");
	render->ReadMesh(L"Plane");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X, 0.0f, Position.Z));
	t->SetScale(FVector(100, 15, 100));
	t->UpdateWorld();

	CMaterial* material = render->GetMaterial("WorldGridMaterial");
	material->SetTiling(FVector2D(6, 6));
	Renders.push_back(render);
}

void CDemo::CreateAirplane()
{
	Shader = CShaders::Get()->GetShader(ShaderFile);
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Airplane");
	render->ReadMesh(L"Airplane");


	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(100.5f, 11.5f, 64.0f));
	t->SetScale(100.0f);
	t->UpdateWorld();

	Renders.push_back(render);

	DrawModelBone(render);
}

void CDemo::CreateSphere()
{
	Shader = CShaders::Get()->GetShader(ShaderFile);
	CMeshRender* render = new CMeshRender(Shader);
	render->ReadMaterial(MaterialFolder + L"63/Sphere");
	render->ReadMesh(L"Sphere");

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X - 1.0f, 1.0f, Position.Z));
	t->SetScale(5.0f);
	t->UpdateWorld();

	Renders.push_back(render);
}

void CDemo::CreateKachujin()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Kachujin");
	render->ReadMesh(L"Kachujin/Kachujin");
	render->ReadAnimation(L"Kachujin/Idle");
	render->Finish_ReadDatas();

	for (float x = -7.0f; x <= 7.0; x += 1.0f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, .0f, Position.Z + 0.5f));
		t->UpdateWorld();
	}

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::CreateKachujin_Old()
{
	Shader = CShaders::Get()->GetShader(L"Animation.fx");
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Kachujin_Old");
	render->ReadMesh(L"Kachujin_Old/Kachujin_Old");
	render->ReadAnimation(L"Kachujin_Old/Idle");
	render->ReadAnimation(L"Kachujin_Old/Run");
	render->ReadAnimation(L"Kachujin_Old/Salsa");
	render->ReadAnimation(L"Kachujin_Old/Walk");
	render->Finish_ReadDatas();

	int index = 0;
	for (float x = -1.0f; x <= 1.0f; x += 1.0f)
	{
		CTransform* t = render->AddTransform();
		t->SetPosition(FVector(Position.X + x, 0.0f, Position.Z + 0.5f));
		t->UpdateWorld();
		int clip = FMath::Random(0, 3);
		render->ChangeClip(index++, clip);
	}

	Renders.push_back(render);
	//DrawModelBone(render);
}

void CDemo::CreatTurtle()
{
	Shader = CShaders::Get()->GetShader(L"Model.fx");

}

void CDemo::CreateTurtle_Anim()
{
	Shader = CShaders::Get()->GetShader(ShaderFile);
	CAnimRender* render = new CAnimRender(Shader);
	render->ReadMaterial(MaterialFolder + L"Turtle");
	render->ReadMesh(L"Turtle/Turtle");
	render->ReadAnimation(L"Turtle/Idle");
	//render->ReadAnimation(L"Turtle/GuardPose");
	//render->ReadAnimation(L"Turtle/Hit");
	//render->ReadAnimation(L"Turtle/Attack_Scratch");
	render->Finish_ReadDatas();

	int index = 0;

	CTransform* t = render->AddTransform();
	t->SetPosition(FVector(Position.X + 2.0f, 0, Position.Z));
	t->SetScale(1.0f);
	t->UpdateWorld();
	/*int clip = FMath::Random(0, 3);
	render->ChangeClip(index++, clip);*/

	Renders.push_back(render);
}

void CDemo::DrawModelBone(CMeshRender* InMesh)
{
	CShader* shader = CShaders::Get()->GetShader(L"Sphere.fx");
	BoneDebugger = new CSphereDebugDrawer(shader, InMesh);
}

