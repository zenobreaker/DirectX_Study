#pragma once

class CRender2D : public CRenderer
{
public:
	CRender2D(ID3D11ShaderResourceView* InSRV);
	~CRender2D();

	void Tick();
	void Render();

public:
	void SetSRV(ID3D11ShaderResourceView* InSRV);
	void SetViewProjection(const FMatrix& InView, const FMatrix& InProjection);

private:
	struct FDesc
	{
		FMatrix View;
		FMatrix Projection;
	} Data;

private:
	CConstantBuffer* CBuffer;
};