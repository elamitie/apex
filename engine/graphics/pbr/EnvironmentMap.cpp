#include "EnvironmentMap.h"

EnvironmentMap::EnvironmentMap() {
	// Initialize pre-computation shaders for the environment
}

EnvironmentMap::~EnvironmentMap() {
	delete mCaptureBuffer;
	
	delete mEnvironment;
	delete mBdrf;
	delete mPrefilter;
	delete mIrradiance;
	delete mEquirectangular;
}

void EnvironmentMap::Render() {

}