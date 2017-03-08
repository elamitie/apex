#include "rendertarget.h"

RenderTarget::RenderTarget(uint width, uint height)
{
	mColorBuffer = std::make_shared<Texture2D>();
	mDepthBuffer = std::make_shared<Texture2D>();

	glGenFramebuffers(1, &mFrameBuffer);

	mColorBuffer->mInternalFormat = GL_RGBA16F;
	mColorBuffer->mMinFilter = GL_LINEAR;
	mColorBuffer->Generate(width, height, 0);

	mDepthBuffer->mImageFormat = GL_DEPTH_COMPONENT;
	mDepthBuffer->mInternalFormat = GL_DEPTH_COMPONENT;
	mDepthBuffer->mMinFilter = GL_DEPTH_COMPONENT;
	mDepthBuffer->Generate(width, height, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorBuffer->mId, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthBuffer->mId, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("%s\n", "Framebuffer error: not complete.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
	glDeleteFramebuffers(0, &mFrameBuffer);
}

void RenderTarget::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
}

void RenderTarget::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::Begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTarget::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
