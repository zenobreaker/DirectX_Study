#pragma once

#include "Systems/IExecutable.h"

class CRawBufferDemo2 : public IExecutable
{
public:
	void Initialize();

private:
	void Case1();
	void Case2();
	void Case3();
};