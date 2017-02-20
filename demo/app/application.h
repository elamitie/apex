#pragma once

#include "engine/engine.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"
#include "graphics/view/camera.h"
#include "utils/math.h"

class Application : public Engine
{
public:
	void Init() override;
	void Update(float dt) override;
	void Render(float dt) override;
	void Cleanup() override;

private:
	Shader* mShader;
	Texture2D* mTexture;
	Camera* mCamera;

	GLfloat vertices[20] = {
		// Positions         // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // Top Right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint mVbo, mVao, mIbo;
};