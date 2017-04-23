#pragma once

#include "frameBuffer.h"

class RenderTarget {
public:
    RenderTarget();
    RenderTarget(uint width, uint height);
    ~RenderTarget();

    void Render();

    inline int GetOutputTexture() { return mFrameBuffer->GetColorTexture(); }

private:
    FrameBuffer* mFrameBuffer;
};