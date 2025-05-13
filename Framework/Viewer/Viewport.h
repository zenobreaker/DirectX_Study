#pragma once

class CViewport
{
public:
	CViewport(float InWidth, float InHeight, float InX = 0, float InY = 0, float InMinDepth = 0, float InMaxDepth = 1);
	~CViewport();

	void RSSetViewport();

	float GetX() { return Vp.TopLeftX; }
	void SetX(float InValue) { Vp.TopLeftX = InValue; }

	float GetY() { return Vp.TopLeftY; }
	void SetY(float InValue) { Vp.TopLeftY = InValue; }

	float GetWidth() { return Vp.Width; }
	void SetWidth(float InValue) { Vp.Width = InValue; }

	float GetHeight() { return Vp.Height; }
	void SetHeight(float InValue) { Vp.Height = InValue; }

	float GetMinDepth() { return Vp.MinDepth; }
	void SetMinDepth(float InValue) { Vp.MinDepth = InValue; }

	float GetMaxDepth() { return Vp.MaxDepth; }
	void SetMaxDepth(float InValue) { Vp.MaxDepth = InValue; }

private:
	D3D11_VIEWPORT Vp;
};