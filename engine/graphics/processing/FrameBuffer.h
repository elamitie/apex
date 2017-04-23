#pragma once

#include "graphics/window.h"
#include "utils/types.h"

enum DepthBufferType {
    NONE = 0,
    DEPTH_TEXTURE,
    DEPTH_RENDER_BUFFER
};

class FrameBuffer {
public:
    FrameBuffer(uint width, uint height, DepthBufferType depthBufferType, bool hdrEnabled = false);
    ~FrameBuffer();

    void Bind();
    void Unbind();

    void BindForRead();

    void Clear();
    void SetViewport(uint width, uint height);

    inline int GetColorTexture() { return mColorTexture; }
    inline int GetDepthTexture() { return mDepthTexture; }


private:
    void CreateFrameBuffer();
    void CreateColorTexture();
    void CreateDepthTexture();
    void CreateDepthBuffer();

    void Initialize();

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