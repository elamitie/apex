#pragma once

#include "graphics/assets/shader.h"
#include "renderTarget.h"

class PostProcessEffect
{
public:
    PostProcessEffect(ShaderPtr shader);
    virtual ~PostProcessEffect();

    void preRender();
    virtual void render(int texture);
    void postRender();

protected:
    RenderTarget* mRenderTarget;
    ShaderPtr mShader;
};