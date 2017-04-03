#pragma once

#include "graphics/assets/Shader.h"
#include "graphics/assets/Texture.h"
#include "graphics/assets/Cubemap.h"
#include "utils/Math.h"

// Much of this class seems like a lot of code duplication (ignoring existing abstractions)
// but rendering to a cubemap and the specific utilization of the framebuffer makes it
// probably not worth abstracting more, at least not right now. Might get system working with
// existing cubemaps.

class PBRPreComputation {
public:
	PBRPreComputation();
	~PBRPreComputation();

	void SetHDR(Texture2D* hdrTexture);
	Texture2D* GetHDR();

private:
	Shader* mHdrToCubemap;
	Shader* mConvoluteIrradiance;
	Shader* mPrefilter;
	Shader* mBDRF;

	Texture2D* mHdrTexture;
	Cubemap* mEnvironmentMap;
	Cubemap* mIrradianceMap;
	Cubemap* mPrefilterMap;

	unsigned int mCaptureFbo;
	unsigned int mCaptureRbo;
};