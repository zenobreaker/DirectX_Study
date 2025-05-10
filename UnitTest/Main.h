#pragma once

#include "Systems/IExecutable.h"

class Main : public IExecutable
{
public:
	void Initialize();
	void Destroy();

	void Tick();
	void Render();

private:

	void Push(IExecutable* exceute);

private:
	vector<IExecutable*> executes;
};