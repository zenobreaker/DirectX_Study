#pragma once

#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
	void Initialize();
	void Destroy();

	void Tick();

	void PreRender();
	void Render();
	void PostRender();

private:
	void Push(IExecutable* InExecutable);

private:
	vector<IExecutable*> Executes;
};