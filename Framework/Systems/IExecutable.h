#pragma once

class IExecutable
{
public:
	virtual void Initialize() {}
	virtual void Destroy() {}

	virtual void Tick() {}

	virtual void PreRender() {}
	virtual void Render() {}
	virtual void PostRender() {}
};
