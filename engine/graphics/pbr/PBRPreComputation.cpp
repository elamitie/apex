#include "PBRPreComputation.h"
#include "utils/FileSystem.h"

PBRPreComputation::PBRPreComputation() {
	int envWidth, envHeight;
	envWidth = envHeight = 512;
	int irrWidth, irrHeight;
	irrWidth = irrHeight = 32;
	int prefilterWidth, prefilterHeight;
	prefilterWidth = prefilterHeight = 128;

	// @TODO: Initialize Shaders

	// Set up capture framebuffer
	glGenFramebuffers(1, &mCaptureFbo);
	glGenFramebuffers(1, &mCaptureRbo);

	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	glBindRenderbuffer(GL_RENDERBUFFER, mCaptureRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mCaptureRbo);

	// Load HDR Environment Texture
	mHdrTexture = new Texture2D();
	mHdrTexture->LoadHDR(FileSystem::GetPath("resources/textures/environments/newport_loft.hdr"));

	// Create Environment Map
	mEnvironmentMap = new Cubemap();
	mEnvironmentMap->minFilter = GL_LINEAR_MIPMAP_LINEAR;
	mEnvironmentMap->Create(envWidth, envHeight);

	// Create projection and view matrices used to render the HDR texture to the cubemap
	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

	// Convert HDR Texture to Environment Map
	mHdrToCubemap->Enable();
	mHdrToCubemap->SetUniform("hdrTexture", 0);
	mHdrToCubemap->SetUniform("projection", captureProjection);
	mHdrTexture->Bind();

	// Set environment resolution!
	glViewport(0, 0, envWidth, envHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	for (unsigned int i = 0; i < 6; ++i) {
		mHdrToCubemap->SetUniform("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mEnvironmentMap->GetHandle(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the cubemap cube mesh
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Set mipmaps, stops artifacting
	mEnvironmentMap->Bind();
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	mEnvironmentMap->Unbind();

	// Create the Irradiance Map
	mIrradianceMap = new Cubemap();
	mIrradianceMap->Create(irrWidth, irrHeight);
	
	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	glBindRenderbuffer(GL_RENDERBUFFER, mCaptureRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, irrWidth, irrHeight);

	// Perform convolution on the irradiance map
	mConvoluteIrradiance->Enable();
	mConvoluteIrradiance->SetUniform("environmentMap", 0);
	mConvoluteIrradiance->SetUniform("projection", captureProjection);
	mEnvironmentMap->Bind();

	glViewport(0, 0, irrWidth, irrHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	for (unsigned int i = 0; i < 6; ++i) {
		mConvoluteIrradiance->SetUniform("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mIrradianceMap->GetHandle(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the cubemap cube mesh
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create the Prefilter Map
	mPrefilterMap = new Cubemap();
	mPrefilterMap->Create(prefilterWidth, prefilterHeight, true);

	// Create the prefilter with "Monte-Carlo Simulation"
	mPrefilter->Enable();
	mPrefilter->SetUniform("environmentMap", 0);
	mPrefilter->SetUniform("projection", captureProjection);
	mEnvironmentMap->Bind();

	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	unsigned int maxLevels = 5;
	for (unsigned int i = 0; i < maxLevels; ++i) {
		unsigned int mipmapWidth = prefilterWidth * std::pow(0.5, i);
		unsigned int mipmapHeight = prefilterHeight * std::pow(0.5, i);

		glBindRenderbuffer(GL_RENDERBUFFER, mCaptureRbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipmapWidth, mipmapHeight);
		glViewport(0, 0, mipmapWidth, mipmapHeight);

		float roughness = (float)i / (float)(maxLevels - 1);
		mPrefilter->SetUniform("roughness", roughness);

		for (unsigned int j = 0; j < 6; ++j) {
			mPrefilter->SetUniform("view", captureViews[j]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, mPrefilterMap->GetHandle(), i);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render the cubemap cube mesh
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

PBRPreComputation::~PBRPreComputation() {

}

void PBRPreComputation::SetHDR(Texture2D* hdrTexture) {

}

Texture2D* PBRPreComputation::GetHDR() {
	return mHdrTexture;
}