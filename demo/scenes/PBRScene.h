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

private:
	CameraPtr camera;
	SceneNodePtr sphere;
	Sphere* sphereMesh;
	PBRMaterial* plastic;

	Texture2D* plasticAlbedo;
	Texture2D* plasticNormal;
	Texture2D* plasticMetallic;
	Texture2D* plasticRoughness;
	Texture2D* plasticAO;
};