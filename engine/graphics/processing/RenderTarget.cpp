#include "renderTarget.h"

RenderTarget::RenderTarget() {
    mFrameBuffer = nullptr;
}

RenderTarget::RenderTarget(uint width, uint height) {
    mFrameBuffer = new FrameBuffer(width, height, NONE);
}

RenderTarget::~RenderTarget() {
    if (mFrameBuffer != nullptr) delete mFrameBuffer;
}

void RenderTarget::Render() {
    if (mFrameBuffer != nullptr)
        mFrameBuffer->Bind();

    //glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (mFrameBuffer != nullptr)
        mFrameBuffer->Unbind();
}