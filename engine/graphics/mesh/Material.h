#pragma once

#include "MaterialBase.h"

class Material : public MaterialBase 
{
public:
	Material() {};
	virtual ~Material() {};

	void SetAlbedo(Texture2D* albedo, int location);
	void SetNormal(Texture2D* normal, int location);
	void SetMetallic(Texture2D* metallic, int location);
	void SetRoughness(Texture2D* roughness, int location);
	void SetAO(Texture2D* ao, int location);

	void SetData() override;

protected:
	Texture2D* mAlbedo;
	Texture2D* mNormal;
	Texture2D* mMetallic;
	Texture2D* mRoughness;
	Texture2D* mAO;
};