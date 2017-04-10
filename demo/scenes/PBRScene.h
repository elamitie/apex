#pragma once

#include "graphics/scene/Scene.h"
#include "graphics/view/Camera.h"
#include "graphics/pbr/PBRMaterial.h"
#include "graphics/mesh/prefab/Sphere.h"

class PBRScene : public Scene {
public:
	PBRScene(int width, int height) : Scene(width, height) {};

	void Begin() override;
	void Update(double dt) override;
	void End() override;

	void OnChangeMaterial(const std::string& matName) override;

private:
	CameraPtr camera;
	SceneNodePtr sphere;
	Sphere* sphereMesh;
	Material* plastic;
	Material* gold;
	Shader* pbr;
};