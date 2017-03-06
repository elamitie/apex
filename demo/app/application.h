#pragma once

#include "engine/engine.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"
#include "graphics/view/camera.h"
#include "utils/math.h"
#include "graphics/mesh/model.h"

class Application : public Engine
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;

private:
	Shader* mModelShader;
	Camera* mCamera;
	Model* mModel;
};