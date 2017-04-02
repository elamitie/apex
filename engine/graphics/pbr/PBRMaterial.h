#pragma once

#include "graphics/assets/Texture.h"
#include "graphics/assets/Cubemap.h"
#include "graphics/mesh/Material.h"

#include <map>

class PBRMaterial : public Material {
public:
	PBRMaterial();

	void SetData() override;

	void SetAlbedo(TexturePtr albedo, int location);
	void SetNormal(TexturePtr normal, int location);
	void SetMetallic(TexturePtr metallic, int location);
	void SetRoughness(TexturePtr roughness, int location);
	void SetAO(TexturePtr ao, int location);
	void SetBDRF(TexturePtr bdrf, int location);

	void SetIrradianceMap(CubemapPtr irrMap, int location);
	void SetPrefilterMap(CubemapPtr prefilter, int location);

private:
	CubemapPtr mIrradiance;
	CubemapPtr mPrefilter;

	TexturePtr mBDRF;
	TexturePtr mAlbedo;
	TexturePtr mNormal;
	TexturePtr mMetallic;
	TexturePtr mRoughness;
	TexturePtr mAO;
};