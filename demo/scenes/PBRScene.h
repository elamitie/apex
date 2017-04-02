#pragma once

#include "graphics/scene/Scene.h"
#include "graphics/view/Camera.h"

class PBRScene : public Scene {
public:
	PBRScene(int width, int height) : Scene(width, height) {};

	void Begin() override;
	void Update(double dt) override;
	void End() override;

private:
	CameraPtr camera;
	SceneNodePtr nanosuit;

	ShaderPtr reflection; // TEMP
};