#pragma once

#include "utils/Math.h"
#include "graphics/assets/Shader.h"
#include "graphics/view/Camera.h"
#include "graphics/pbr/PBRPreComputation.h"
#include <map>

class Material {
public:
	Material() {};
	virtual ~Material() {};

	void SetInt(const std::string& name, int data);
	void SetFloat(const std::string& name, float data);
	void SetBool(const std::string& name, bool  data);
	void SetVector(const std::string& name, const glm::vec2& data);
	void SetVector(const std::string& name, const glm::vec3& data);
	void SetVector(const std::string& name, const glm::vec4& data);
	void SetMatrix(const std::string& name, const glm::mat4& data);

	virtual void SetAlbedo(Texture2D* albedo, int location);
	virtual void SetNormal(Texture2D* normal, int location);
	virtual void SetMetallic(Texture2D* metallic, int location);
	virtual void SetRoughness(Texture2D* roughness, int location);
	virtual void SetAO(Texture2D* ao, int location);
	virtual void SetBRDF(Texture2D* brdf, int location);

	virtual void SetData();
	
	// Each child Material can be either a PBR or a Lambert Material;
	// Set the relevant "background".
	// @Refactor: This API design is stupid make a new one
	virtual void SetSkybox(SkyboxPtr skybox) {};

	void Enable();
	void Disable();

	inline void SetShader(Shader* shader) { mShader = shader; }
	inline void SetCamera(CameraPtr camera) { mCamera = camera; }

	void SetEnvironmentMap(PBRPreComputation* precompute);

private:
	void SetIrradianceMap(Cubemap* irrMap, int location);
	void SetPrefilterMap(Cubemap* prefilter, int location);

protected:
	Cubemap*   mIrradiance;
	Cubemap*   mPrefilter;
	Texture2D* mBRDF;

	Texture2D* mAlbedo;
	Texture2D* mNormal;
	Texture2D* mMetallic;
	Texture2D* mRoughness;
	Texture2D* mAO;

	Shader* mShader;
	CameraPtr mCamera;
	std::map<std::string, int> mBindingLocations;
};