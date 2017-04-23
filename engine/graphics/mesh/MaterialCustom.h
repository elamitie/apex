#pragma once

#include "MaterialBase.h"
#include "utils/Color.h"

class MaterialCustom : public MaterialBase
{
	friend class ForwardRenderer;
public:
	MaterialCustom() {};
	virtual ~MaterialCustom() {};

	void SetAlbedo(Color& color);
	void SetMetallic(float metallic);
	void SetRoughness(float roughness);
	void SetAO(float ao);

	void SetData() override;

private:
	Color mAlbedo;
	float mMetallic;
	float mRoughness;
	float mAO;
};