#include "postProcessEffect.h"

PostProcessEffect::PostProcessEffect(ShaderPtr shader)
{
    mRenderTarget = new RenderTarget();
    mShader = shader;
}

PostProcessEffect::~PostProcessEffect()
{
    delete mRenderTarget;
}

void PostProcessEffect::preRender()
{
    mShader->enable();
}

void PostProcessEffect::render(int texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    mShader->setUniform("postProcess_texture", 0);

    mRenderTarget->render();
}

void PostProcessEffect::postRender()
{
    mShader->disable();
}