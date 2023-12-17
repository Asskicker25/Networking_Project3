#include "RendererInstance.h"

RendererInstance::RendererInstance()
{
}

RendererInstance& RendererInstance::GetInstance()
{
    static RendererInstance instance;
    return instance;
}

void RendererInstance::SetRenderer(Renderer* renderer)
{
    this->renderer = renderer;
}

Renderer* RendererInstance::GetRenderer()
{
    return renderer;
}
