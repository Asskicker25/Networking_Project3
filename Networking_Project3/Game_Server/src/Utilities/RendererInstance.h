#pragma once

#include <Graphics/Renderer.h>

class RendererInstance
{
private:
	Renderer* renderer;

public:
	RendererInstance();

	static RendererInstance& GetInstance();
	void SetRenderer(Renderer* renderer);
	Renderer* GetRenderer();
	
};