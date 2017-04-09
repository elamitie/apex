#pragma once

#include "graphics/processing/FrameBuffer.h"

class EnvironmentMap {
public:
	EnvironmentMap();
	~EnvironmentMap();

	void Render();

private:
	Shader* mEquirectangular;
	Shader* mIrradiance;
	Shader* mPrefilter;
	Shader* mbrdf;
	Shader* mEnvironment;

	FrameBuffer* mCaptureBuffer;
};