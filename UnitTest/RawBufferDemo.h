#pragma once

#include "Systems/IExecutable.h"

class CRawBufferDemo : public IExecutable
{
public:
	void Initialize();
	void Destroy();
};