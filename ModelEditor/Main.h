#pragma once

#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
	void Initialize();

private:
	void Cube();
	void Sphere();
	void Cone();
	void Cylinder();
	void Plane();

	void Airplane();

	void Kachujin_Old();
	void Kachujin();

	void Turtle();
};