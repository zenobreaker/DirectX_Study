#pragma once

#include "Framework.h"

//------------------------------------------------------------------------------

struct FVertex
{
	FVertex()
		: Position(0, 0, 0) {}

	FVertex(FVector p)
		: Position(p) { }

	FVector Position;
};

//------------------------------------------------------------------------------

struct FVertexColor
{
	FVertexColor()
		: Position(0, 0, 0)
		, FColor(0, 0, 0, 1) {}

	FVertexColor(FVector p, FColor c)
		: Position(p)
		, FColor(c) {}

	FVector Position;
	FColor FColor;
};

//------------------------------------------------------------------------------

struct FVertexTexture
{
	FVertexTexture()
		: Position(0, 0, 0)
		, Uv(0, 0) {}

	FVertexTexture(FVector p, FVector2D c)
		: Position(p)
		, Uv(c) {}

	FVector Position;
	FVector2D Uv;
};

//------------------------------------------------------------------------------

struct FVertexTextureColor
{
	FVertexTextureColor()
		: Position(0, 0, 0)
		, Uv(0, 0)
		, FColor(0, 0, 0, 1) {}

	FVector Position;
	FVector2D Uv;
	FColor FColor;
};

//------------------------------------------------------------------------------

struct FVertexNormal
{
	FVertexNormal()
		: Position(0, 0, 0)
		, Normal(0, 0, 0) {}

	FVector Position;
	FVector Normal;
};

struct FVertexTextureNormal
{
	FVertexTextureNormal()
		: Position(0, 0, 0)
		, Uv(0, 0)
		, Normal(0, 0, 0) {
	}

	FVector Position;
	FVector2D Uv;
	FVector Normal;
};

//------------------------------------------------------------------------------

struct FVertexModel
{
	FVector Position;
	FVector2D Uv;
	FColor Color;
	FVector Normal;
	FVector Tangent;
	FVector4 Indices; //int4
	FVector4 Weights; //float4
};