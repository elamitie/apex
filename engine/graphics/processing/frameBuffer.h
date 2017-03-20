#pragma once

#include "graphics/window.h"
#include "utils/types.h"

enum DepthBufferType
{
    NONE = 0,
    DEPTH_TEXTURE,
    DEPTH_RENDER_BUFFER
};

class FrameBuffer
{
public:
    FrameBuffer(uint width, uint height, DepthBufferType depthBufferType, bool hdrEnabled = false);
    ~FrameBuffer();

    void bind();
    void unbind();

    void bindForRead();

    inline int getColorTexture() { return mColorTexture; }
    inline int getDepthTexture() { return mDepthTexture; }


private:
    void createFrameBuffer();
    void createColorTexture();
    void createDepthTexture();
    void createDepthBuffer();

    void initialize();

private:
    uint mWidth, mHeight;
    bool mHdrEnabled;

    // Storing these textures as ints rather than engine textures because its
    // easier to track internally. Can always create an engine texture from an
    // existing id in the future?
    GLuint mColorTexture, mDepthTexture;
    GLuint mColorBuffer, mDepthBuffer;

    GLuint mFrameBuffer;

    DepthBufferType mDepthType;
};