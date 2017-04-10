#pragma once

#include "graphics/pbr/PBRMaterial.h"
#include <map>

enum MaterialType { Phong, PBR };

class MaterialCache {
public:

	static Material* GetMaterial(const std::string& dir, MaterialType type);

private:
	MaterialCache() {}
	~MaterialCache() {}

	static std::map<std::string, Material*> mMaterials;
	static std::map<std::string, PBRMaterial*> mPBRMaterials;
};