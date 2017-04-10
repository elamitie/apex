#include "Material.h"

void Material::SetInt(const std::string& name, int data)
{
	mShader->SetUniform(name, data);
}

void Material::SetFloat(const std::string& name, float data)
{
	mShader->SetUniform(name, data);
}

void Material::SetBool(const std::string& name, bool data)
{
	mShader->SetUniform(name, data);
}

void Material::SetVector(const std::string& name, const glm::vec2& data)
{
	mShader->SetUniform(name, data);
}

void Material::SetVector(const std::string& name, const glm::vec3& data)
{
	mShader->SetUniform(name, data);
}

void Material::SetVector(const std::string& name, const glm::vec4& data)
{
	mShader->SetUniform(name, data);
}

void Material::SetMatrix(const std::string& name, const glm::mat4& data)
{
	mShader->SetUniform(name, data);
}

void Material::Enable()
{
	mShader->Enable();
}

void Material::Disable()
{
	mShader->Disable();
}

void Material::SetData() {
	// Set all of this shader's uniforms
	// @TODO: Take in a vector of PointLights! These are hardcoded for now!
	if (mCamera) mShader->SetUniform("camPos", mCamera->Position);

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3(10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
		std::string position = "lightPositions[" + std::to_string(i) + "]";
		std::string color = "lightColors[" + std::to_string(i) + "]";

		mShader->SetUniform(position, lightPositions[i]);
		mShader->SetUniform(color, lightColors[i]);
	}

	for (auto& uniform : mBindingLocations) {
		mShader->SetUniform(uniform.first, uniform.second);
	}

	mIrradiance->Bind(mBindingLocations["irradianceMap"]);
	mPrefilter->Bind(mBindingLocations["prefilterMap"]);
	mBRDF->Bind(mBindingLocations["brdfLUT"]);
	mAlbedo->Bind(mBindingLocations["albedoMap"]);
	mNormal->Bind(mBindingLocations["normalMap"]);
	mMetallic->Bind(mBindingLocations["metallicMap"]);
	mRoughness->Bind(mBindingLocations["roughnessMap"]);
	mAO->Bind(mBindingLocations["aoMap"]);
}

void Material::SetAlbedo(Texture2D* albedo, int location)
{
	mAlbedo = albedo;
	mBindingLocations["albedoMap"] = location;
}

void Material::SetNormal(Texture2D* normal, int location)
{
	mNormal = normal;
	mBindingLocations["normalMap"] = location;
}

void Material::SetMetallic(Texture2D* metallic, int location)
{
	mMetallic = metallic;
	mBindingLocations["metallicMap"] = location;
}

void Material::SetRoughness(Texture2D* roughness, int location)
{
	mRoughness = roughness;
	mBindingLocations["roughnessMap"] = location;
}

void Material::SetAO(Texture2D* ao, int location)
{
	mAO = ao;
	mBindingLocations["aoMap"] = location;
}

void Material::SetBRDF(Texture2D* brdf, int location)
{
	mBRDF = brdf;
	mBindingLocations["brdfLUT"] = location;
}

void Material::SetIrradianceMap(Cubemap* irrMap, int location)
{
	mIrradiance = irrMap;
	mBindingLocations["irradianceMap"] = location;
}

void Material::SetPrefilterMap(Cubemap* prefilter, int location)
{
	mPrefilter = prefilter;
	mBindingLocations["prefilterMap"] = location;
}

void Material::SetEnvironmentMap(PBRPreComputation* precompute) {
	SetIrradianceMap(precompute->GetIrradianceMap(), 0);
	SetPrefilterMap(precompute->GetPrefilterMap(), 1);
	SetBRDF(precompute->GetBRDF(), 2);
}
