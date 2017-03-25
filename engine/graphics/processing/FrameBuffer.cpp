#include "frameBuffer.h"

FrameBuffer::FrameBuffer(uint width, uint height, DepthBufferType depthBufferType, bool hdrEnabled) {
    mWidth = width;
    mHeight = height;
    mDepthType = depthBufferType;
    mHdrEnabled = hdrEnabled;
    initialize();
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &mFrameBuffer);
    glDeleteRenderbuffers(1, &mDepthBuffer);
    glDeleteRenderbuffers(1, &mColorBuffer);
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffer);
    glViewport(0, 0, mWidth, mHeight);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600);
}

void FrameBuffer::bindForRead() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFrameBuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::createFrameBuffer() {
    glGenFramebuffers(1, &mFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::createColorTexture() {
    glGenTextures(1, &mColorTexture);

    GLenum internalFormat = mHdrEnabled ? GL_RGBA16F : GL_RGBA8;

    glBindTexture(GL_TEXTURE_2D, mColorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexture, 0);
}

void FrameBuffer::createDepthTexture() {
    glGenTextures(1, &mDepthTexture);

    glBindTexture(GL_TEXTURE_2D, mDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0);
}

void FrameBuffer::createDepthBuffer() {
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mWidth, mHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
}

void FrameBuffer::initialize() {
    createFrameBuffer();
    createColorTexture();

    switch (mDepthType) {
    case DEPTH_RENDER_BUFFER:
        createDepthBuffer();
        break;
    case DEPTH_TEXTURE:
        createDepthTexture();
        break;
    default:
        break;
    }

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    unbind();
}