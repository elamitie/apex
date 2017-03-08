#include "graphics/window.h"
#include "utils/types.h"
#include "graphics/assets/texture.h"

class RenderTarget
{
public:
	RenderTarget(uint width, uint height);
	~RenderTarget();

	void Bind();
	void Unbind();

	void Begin();
	void End();

private:
	TexturePtr mColorBuffer;
	TexturePtr mDepthBuffer;
	uint width, height;

	GLuint mFrameBuffer;
	GLuint mRenderBuffer;
};