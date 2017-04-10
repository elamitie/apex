#pragma once

#include "graphics/assets/Texture.h"
#include "graphics/assets/Cubemap.h"
#include "graphics/mesh/Material.h"

#include <map>

class PBRMaterial : public Material {
public:
	PBRMaterial();

	/*void SetData() override;

	void SetAlbedo(Texture2D* albedo, int location);
	void SetNormal(Texture2D* normal, int location);
	void SetMetallic(Texture2D* metallic, int location);
	void SetRoughness(Texture2D* roughness, int location);
	void SetAO(Texture2D* ao, int location);
	void SetBRDF(Texture2D* brdf, int location);*/

	//void SetEnvironmentMap(PBRPreComputation* precompute) override;

private:
	//void SetIrradianceMap(Cubemap* irrMap, int location);
	//void SetPrefilterMap(Cubemap* prefilter, int location);

private:
	Cubemap* mIrradiance;
	Cubemap* mPrefilter;
	Texture2D* mBRDF;

	Texture2D* mAlbedo;
	Texture2D* mNormal;
	Texture2D* mMetallic;
	Texture2D* mRoughness;
	Texture2D* mAO;
};