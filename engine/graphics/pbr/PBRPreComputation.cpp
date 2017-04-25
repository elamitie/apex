#include "PBRPreComputation.h"
#include "utils/FileSystem.h"

PBRPreComputation::PBRPreComputation(const std::string& envName) {
	int envWidth, envHeight;
	envWidth = envHeight = 512;
	int irrWidth, irrHeight;
	irrWidth = irrHeight = 32;
	int prefilterWidth, prefilterHeight;
	prefilterWidth = prefilterHeight = 128;
	int brdfWidth, brdfHeight;
	brdfWidth = brdfHeight = 512;

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	CreateCube();
	CreateQuad();
	InitializeShaders();

	// Set up capture framebuffer
	glGenFramebuffers(1, &mCaptureFbo);
	glGenFramebuffers(1, &mCaptureRbo);

	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	glBindRenderbuffer(GL_RENDERBUFFER, mCaptureRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mCaptureRbo);

	// Load HDR Environment Texture
	mHdrTexture = new Texture2D();
	mHdrTexture->LoadHDR(FileSystem::GetPath("resources/textures/environments/" + envName + ".hdr"));

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
		glBindVertexArray(mCubeVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
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
		glBindVertexArray(mCubeVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create the Prefilter Map
	mPrefilterMap = new Cubemap();
	mPrefilterMap->minFilter = GL_LINEAR_MIPMAP_LINEAR;
	mPrefilterMap->magFilter = GL_LINEAR;
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
			glBindVertexArray(mCubeVao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// brdf Integration
	mBRDFTexture = new Texture2D();
	mBRDFTexture->mInternalFormat = GL_RG16F;
	mBRDFTexture->mImageFormat = GL_RG;
	mBRDFTexture->mMinFilter = GL_LINEAR;
	mBRDFTexture->mMaxFilter = GL_LINEAR;
	mBRDFTexture->Generate(brdfWidth, brdfHeight, nullptr, true);

	glBindFramebuffer(GL_FRAMEBUFFER, mCaptureFbo);
	glBindRenderbuffer(GL_RENDERBUFFER, mCaptureRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, brdfWidth, brdfHeight);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mBRDFTexture->GetHandle(), 0);

	glViewport(0, 0, brdfWidth, brdfHeight);
	mBRDF->Enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render Quad
	glBindVertexArray(mQuadVao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 1280, 720);
}

void PBRPreComputation::RenderBRDF() {
	mBRDF->Enable();
	glBindVertexArray(mQuadVao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

PBRPreComputation::~PBRPreComputation() {
	delete mPrefilterMap;
	delete mIrradianceMap;
	delete mEnvironmentMap;
	delete mBRDFTexture;
	delete mHdrTexture;

	delete mBRDF;
	delete mPrefilter;
	delete mConvoluteIrradiance;
	delete mHdrToCubemap;

	glDeleteBuffers(1, &mCaptureRbo);
	glDeleteBuffers(1, &mCaptureFbo);
}

void PBRPreComputation::SetHDR(Texture2D* hdrTexture) {

}

Texture2D* PBRPreComputation::GetHDR() {
	return mHdrTexture;
}

void PBRPreComputation::InitializeShaders() {
	mHdrToCubemap = new Shader();
	mHdrToCubemap->SetDebug(true);
	mHdrToCubemap->Attach("pbr/cubemap.vert")->Attach("pbr/hdr_to_cubemap.frag")->Link();

	mConvoluteIrradiance = new Shader();
	mConvoluteIrradiance->SetDebug(true);
	mConvoluteIrradiance->Attach("pbr/cubemap.vert")->Attach("pbr/convolute_irradiance.frag")->Link();

	mPrefilter = new Shader();
	mPrefilter->SetDebug(true);
	mPrefilter->Attach("pbr/cubemap.vert")->Attach("pbr/prefilter.frag")->Link();

	mBRDF = new Shader();
	mBRDF->SetDebug(true);
	mBRDF->Attach("pbr/integrate_brdf.vert")->Attach("pbr/integrate_brdf.frag")->Link();
}

void PBRPreComputation::CreateCube() {
	GLfloat vertices[] = {
        // Back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  // Bottom-left
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  // top-right
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right         
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  // top-right
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  // top-left
        // Front face
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // bottom-left
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,  // bottom-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  // top-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  // top-right
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  // top-left
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // bottom-left
        // Left face
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // top-right
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  // top-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // bottom-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // bottom-left
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // bottom-right
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // top-right
        // Right face
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // top-left
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // bottom-right
         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  // top-right         
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // bottom-right
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // top-left
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // bottom-left     
        // Bottom face
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  // top-right
         1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  // top-left
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  // bottom-left
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  // bottom-left
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,  // bottom-right
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  // top-right
        // Top face
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  // top-left
         1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  // bottom-right
         1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // top-right     
         1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  // bottom-right
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  // top-left
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f   // bottom-left        
    };

    glGenVertexArrays(1, &mCubeVao);
    glGenBuffers(1, &mCubeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mCubeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(mCubeVao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PBRPreComputation::CreateQuad() {
	GLfloat quadVertices[] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	glGenVertexArrays(1, &mQuadVao);
	glGenBuffers(1, &mQuadVbo);
	glBindVertexArray(mQuadVao);
	glBindBuffer(GL_ARRAY_BUFFER, mQuadVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}