#pragma once

#include "utils/Math.h"
#include "graphics/assets/Shader.h"
#include "graphics/view/Camera.h"
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

	virtual void SetData() = 0;
	
	// Each child Material can be either a PBR or a Lambert Material;
	// Set the relevant "background".
	// @Refactor: This API design is stupid make a new one
	virtual void SetSkybox(SkyboxPtr skybox) {};
	virtual void SetEnvironmentMap() {};


	void Enable();
	void Disable();

	inline void SetShader(ShaderPtr shader) { mShader = shader; }
	inline void SetCamera(CameraPtr camera) { mCamera = camera; }

protected:
	ShaderPtr mShader;
	CameraPtr mCamera;
	std::map<std::string, int> mBindingLocations;
};