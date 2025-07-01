#pragma once

#include "Systems/IExecutable.h"

class CTextureBufferDemo: public IExecutable
{
public:
	void Initialize();
	void Destroy(); 
	void Tick(); 
	void Render(); 

private:
	void Case1(); 
	void Case2(); 
	void Case3(); 

private:
	CTexture* Image;
	CTexture* Image2;
	CTextureBuffer* TBuffer;
	CTextureBuffer* TBuffer2;

	CRender2D* Render2D; 
};