#pragma once

#include "graphics/scene/Scene.h"
#include "graphics/view/Camera.h"
#include "graphics/mesh/prefab/Sphere.h"

#include "graphics/mesh/Material.h"
#include "graphics/mesh/MaterialCustom.h"

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
	MaterialCustom* custom;
	Shader* pbr;
	Shader* pbrCustom;

	float targetRotation;

	double fuck = 0.0;
};