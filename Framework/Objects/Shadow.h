#pragma once


class CShadow
{
public:
	CShadow(FVector InPosition, float InRadius, UINT InWidth = 1024, UINT InHeight = 1024);
	~CShadow();

	void Tick(); 
	void PreRedner();

	operator ID3D11ShaderResourceView* () { return *Target; }
	operator const ID3D11ShaderResourceView* () { return *Target; }

public:
	UINT GetWidth() const { return Width; }
	UINT GetHeight() const { return Height; }

	FMatrix GetView() const { return View; }
	FMatrix GetProjection() const { return Projection; }

	FVector& GetPosition() { return Position; }
	float GetRaidus() const { return Radius; }
	float GetBias() const { return Bias; }
	UINT GetQuaility() const { return Quality; }

public:
	void CalcViewProjection();


private:
	UINT Width, Height;

	FMatrix View;
	FMatrix Projection;

	FVector Position;
	float Radius;
	float Bias = 0.0001f; 
	UINT Quality = 0;

	CRenderTarget* Target;
	CDepthStencil* Depth;
	CViewport* Vp;

};