#pragma once

#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
	void Initialize();

private:
	void Cube();
	void Airplane();
};