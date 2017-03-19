#pragma once

#include "frameBuffer.h"

class RenderTarget
{
public:
    RenderTarget();
    RenderTarget(uint width, uint height);
    ~RenderTarget();

    void render();

    inline int getOutputTexture() { return mFrameBuffer->getColorTexture(); }

private:
    FrameBuffer* mFrameBuffer;
};