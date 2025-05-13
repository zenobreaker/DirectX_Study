#include "Framework.h"
#include "Particle.h"
#include <fstream>

void CParticle::ReadFile(wstring InFileName)
{
	ifstream stream;
	stream.open(InFileName);

	Json::Value root;
	stream >> root;

	Json::Value::Members members = root.getMemberNames();
	for (UINT i = 0; i < members.size(); i++)
	{
		string name = members[i];
		const Json::Value& value = root[name];

		if(name == "1_Settgins") ReadSettings(value);
		if (name == "2_Velocity") ReadVelocity(value);
		if (name == "3_Speed") ReadSpeed(value);
		if (name == "4_Size") ReadSize(value);
		if (name == "5_Color") ReadColor(value);
	}
}

void CParticle::ReadSettings(const Json::Value& value)
{
	ParticleData.Type = (FParticleData::EBlendType)stoi(value["00_BlendType"].asString());
	ParticleData.bLoop = (bool)stoi(value["01_bLoop"].asString());

	ParticleData.TextureFile = CString::ToWString(value["02_TextureFile"].asString());
	ParticleData.TextureFile = ParticleData.TextureFile;
	Texture = new CTexture(Shader, "ParticleMap", ParticleData.TextureFile);

	ParticleData.MaxParticle = (UINT)stoi(value["03_MaxParticle"].asString());
	ParticleData.ReadyTime = stof(value["04_ReadyTime"].asString());
	ParticleData.ReadyRandomTime = stof(value["05_ReadyRandomTime"].asString());

	vector<string> v;
	CString::SplitString(&v, value["06_Gravity"].asString(), ",");
	ParticleData.Gravity = FVector(stof(v[0]), stof(v[1]), stof(v[2]));
}

void CParticle::ReadVelocity(const Json::Value& value)
{
	ParticleData.StartVelocity = stof(value["00_StartVelocity"].asString());
	ParticleData.EndVelocity = stof(value["01_EndVelocity"].asString());
	ParticleData.MinHorizontalVelocity = stof(value["02_MinHorizontalVelocity"].asString());
	ParticleData.MaxHorizontalVelocity = stof(value["03_MaxHorizontalVelocity"].asString());
	ParticleData.MinVerticalVelocity = stof(value["04_MinVerticalVelocity"].asString());
	ParticleData.MaxVerticalVelocity = stof(value["05_MaxVerticalVelocity"].asString());
}

void CParticle::ReadSpeed(const Json::Value& value)
{
	ParticleData.MinRotateSpeed = stof(value["00_MinRotateSpeed"].asString());
	ParticleData.MaxRotateSpeed = stof(value["01_MaxRotateSpeed"].asString());
}

void CParticle::ReadSize(const Json::Value& value)
{
	ParticleData.MinStartSize = stof(value["00_MinStartSize"].asString());
	ParticleData.MaxStartSize = stof(value["01_MaxStartSize"].asString());
	ParticleData.MinEndSize = stof(value["02_MinEndSize"].asString());
	ParticleData.MaxEndSize = stof(value["03_MaxEndSize"].asString());
}

void CParticle::ReadColor(const Json::Value& value)
{
	ParticleData.ColorAmount = stof(value["00_ColorAmount"].asString());


	vector<string> color;

	CString::SplitString(&color, value["01_MinColor"].asString(), ",");
	ParticleData.MinColor = FColor(stof(color[0]), stof(color[1]), stof(color[2]), stof(color[3]));

	CString::SplitString(&color, value["02_MaxColor"].asString(), ",");
	ParticleData.MaxColor = FColor(stof(color[0]), stof(color[1]), stof(color[2]), stof(color[3]));
}

