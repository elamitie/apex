#include "postProcessEffect.h"

PostProcessEffect::PostProcessEffect(ShaderPtr shader) {
    mRenderTarget = new RenderTarget();
    mShader = shader;
}

PostProcessEffect::~PostProcessEffect() {
    delete mRenderTarget;
}

void PostProcessEffect::PreRender() {
    mShader->Enable();
}

void PostProcessEffect::Render(int texture) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    mShader->SetUniform("postProcess_texture", 0);

    mRenderTarget->Render();
}

void PostProcessEffect::PostRender() {
    mShader->Disable();
}