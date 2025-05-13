#pragma once

class CRender2D : public CRenderer
{
public:
	CRender2D(ID3D11ShaderResourceView* InSRV);
	~CRender2D();

	void Tick();
	void Render();

private:
	struct FDesc
	{
		FMatrix View;
		FMatrix Projection;
	} Data;

private:
	CConstantBuffer* CBuffer;
};