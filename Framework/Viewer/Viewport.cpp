#include "Framework.h"
#include "Viewport.h"

CViewport::CViewport(float InWidth, float InHeight, float InX, float InY, float InMinDepth, float InMaxDepth)
{
	Vp.TopLeftX = InX;
	Vp.TopLeftY = InY;
	Vp.Width = InWidth;
	Vp.Height = InHeight;
	Vp.MinDepth = InMinDepth;
	Vp.MaxDepth = InMaxDepth;
}

CViewport::~CViewport()
{

}

void CViewport::RSSetViewport()
{
	CD3D::Get()->GetDeviceContext()->RSSetViewports(1, &Vp);
}
