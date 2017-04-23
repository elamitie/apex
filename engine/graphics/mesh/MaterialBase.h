#pragma once

#include "utils/Math.h"
#include "graphics/assets/Shader.h"
#include "graphics/view/Camera.h"
#include "graphics/pbr/PBRPreComputation.h"
#include <map>

class MaterialBase
{
public:
	MaterialBase() {};
	virtual ~MaterialBase() {};

	inline void SetInt(const std::string& name, int data) { mShader->SetUniform(name, data); }
	inline void SetFloat(const std::string& name, float data) { mShader->SetUniform(name, data); }
	inline void SetBool(const std::string& name, bool  data) { mShader->SetUniform(name, data); }
	inline void SetVector(const std::string& name, const glm::vec2& data) { mShader->SetUniform(name, data); }
	inline void SetVector(const std::string& name, const glm::vec3& data) { mShader->SetUniform(name, data); }
	inline void SetVector(const std::string& name, const glm::vec4& data) { mShader->SetUniform(name, data); }
	inline void SetMatrix(const std::string& name, const glm::mat4& data) { mShader->SetUniform(name, data); }

	void SetEnvironmentMap(PBRPreComputation* precompute)
	{
		SetIrradianceMap(precompute->GetIrradianceMap(), 0);
		SetPrefilterMap(precompute->GetPrefilterMap(), 1);
		SetBRDF(precompute->GetBRDF(), 2);
	}

	inline void Enable() { mShader->Enable(); }
	inline void Disable() { mShader->Disable(); }

	inline void SetShader(Shader* shader) { mShader = shader; }
	inline void SetCamera(CameraPtr camera) { mCamera = camera; }
	
	virtual void SetData()
	{
		mIrradiance->Bind(mBindingLocations["irradianceMap"]);
		mPrefilter->Bind(mBindingLocations["prefilterMap"]);
		mBRDF->Bind(mBindingLocations["brdfLUT"]);
	}
	
	virtual void SetSkybox(SkyboxPtr skybox) {};

protected:
	void SetIrradianceMap(Cubemap* irrMap, int location)
	{
		mIrradiance = irrMap;
		mBindingLocations["irradianceMap"] = location;
	}
	
	void SetPrefilterMap(Cubemap* prefilter, int location)
	{
		mPrefilter = prefilter;
		mBindingLocations["prefilterMap"] = location;
	}

	void SetBRDF(Texture2D* brdf, int location)
	{
		mBRDF = brdf;
		mBindingLocations["brdfLUT"] = location;
	}

	Cubemap*   mIrradiance;
	Cubemap*   mPrefilter;
	Texture2D* mBRDF;

	Shader* mShader;
	CameraPtr mCamera;
	std::map<std::string, int> mBindingLocations;
};