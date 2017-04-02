#pragma once

#include "graphics/scene/Scene.h"
#include "graphics/view/Camera.h"
#include "graphics/mesh/ReflectionMaterial.h"
#include "graphics/mesh/prefab/Sphere.h"

class ReflectionScene : public Scene {
public:
	ReflectionScene(int width, int height) : Scene(width, height) {};

	void Begin() override;
	void Update(double dt) override;
	void End() override;

private:
	ReflectionMaterial* reflection;
	Sphere* sphereMesh;
	SceneNodePtr sphere;
	CameraPtr camera;
};