#include "Framework.h"
#include "DynamicCubeMap.h"

CDynamicCubeMap::CDynamicCubeMap(CShader* InShader)
	: Shader(InShader)
{
	RenderTarget = new CRenderTarget(Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, true);
	DepthStencil = new CDepthStencil(Width, Height, false, true);
	Viewport = new CViewport(Width, Height);

	CBuffer = new CConstantBuffer(Shader, "CB_DynamicCubeMap", &Data, sizeof(FDesc));

	sDynamicCubeMap = Shader->AsSRV("DynamicCubeMap");
}

CDynamicCubeMap::~CDynamicCubeMap()
{
	Delete(RenderTarget);
	Delete(DepthStencil);
	Delete(Viewport);
	Delete(CBuffer);
}

void CDynamicCubeMap::Tick()
{

}

void CDynamicCubeMap::PreRender(const FVector& InPosition, const FVector& InScale)
{
	//Create View Matricies
	{
		float x = InPosition.X;
		float y = InPosition.Y;
		float z = InPosition.Z;


		struct FTarget
		{
			FVector LookAt;
			FVector Up;
		} targets[6];

		targets[0] = { FVector(x + InScale.X, y, z), FVector(0, 1, 0) };
		targets[1] = { FVector(x - InScale.X, y, z), FVector(0, 1, 0) };
		targets[2] = { FVector(x, y + InScale.Y, z), FVector(0, 0, -1)};
		targets[3] = { FVector(x, y - InScale.Y, z), FVector(0, 0, +1)};
		targets[4] = { FVector(x, y, z + InScale.Z), FVector(0, 1, 0) };
		targets[5] = { FVector(x, y, z - InScale.Z), FVector(0, 1, 0) };

		for (int i = 0; i < 6; i++)
			Data.Views[i] = FMatrix::CreateLookAt(InPosition, targets[i].LookAt, targets[i].Up);
	}


	CBuffer->Render();

	if (FMath::IsZero(FOV))
		Data.Projection = FMatrix::CreateOrthographic(Width, Height, Near, Far);
	else
		Data.Projection = FMatrix::CreatePerspectiveFieldOfView(FMath::Pi * FOV, Width / Height, Near, Far);


	RenderTarget->OMSetRenderTarget(DepthStencil);
	RenderTarget->ClearRenderTarget();
	DepthStencil->ClearDepthStencil();
	Viewport->RSSetViewport();
}

void CDynamicCubeMap::Render()
{
	sDynamicCubeMap->SetResource(*RenderTarget);
}
