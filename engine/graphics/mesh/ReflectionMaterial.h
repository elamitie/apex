#pragma once

#include "Material.h"
#include "graphics/view/Skybox.h"

class ReflectionMaterial : public Material {
public:
	ReflectionMaterial();

	void SetData() override;
	void SetSkybox(SkyboxPtr skybox) override;

private:
	SkyboxPtr mSkybox;
};