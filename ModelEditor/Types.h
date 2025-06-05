#pragma once
#include "Pch.h"

struct FMaterialData
{
	string Name; 
	string ShaderName; 

	FColor Ambient;
	FColor Diffuse; 
	FColor Specular; 
	FColor Emissive;

	string DiffuseFile;
	string SpecularFile; 
	string NormalFile; 
};
