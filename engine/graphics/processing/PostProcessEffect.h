#pragma once

#include "graphics/assets/shader.h"
#include "renderTarget.h"

class PostProcessEffect {
public:
    PostProcessEffect(ShaderPtr shader);
    virtual ~PostProcessEffect();

    void PreRender();
    virtual void Render(int texture);
    void PostRender();

protected:
    RenderTarget* mRenderTarget;
    ShaderPtr mShader;
};