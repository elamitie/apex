#include "PBRMaterial.h"

PBRMaterial::PBRMaterial() {
	mIrradiance = nullptr;
	mPrefilter = nullptr;
	mBRDF = nullptr;

	mAlbedo = nullptr;
	mNormal = nullptr;
	mMetallic = nullptr;
	mRoughness = nullptr;
	mAO = nullptr;

	mShader = new Shader();
	mShader->SetDebug(true);
	mShader->Attach("pbr/pbr.vert")->Attach("pbr/pbr.frag")->Link();
	mShader->AddAttribs({ "position", "normal", "texCoords" });
}

void PBRMaterial::SetData() {
	// Set all of this shader's uniforms
	// @TODO: Take in a vector of PointLights! These are hardcoded for now!
	if (mCamera) mShader->SetUniform("camPos", mCamera->Position);

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3( 10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3( 10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
		std::string position = "lightPositions[" + std::to_string(i) + "]";
		std::string color    = "lightColors[" + std::to_string(i) + "]";

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

void PBRMaterial::SetAlbedo(Texture2D* albedo, int location)
{
	mAlbedo = albedo;
	mBindingLocations["albedoMap"] = location;
}

void PBRMaterial::SetNormal(Texture2D* normal, int location)
{
	mNormal = normal;
	mBindingLocations["normalMap"] = location;
}

void PBRMaterial::SetMetallic(Texture2D* metallic, int location)
{
	mMetallic = metallic;
	mBindingLocations["metallicMap"] = location;
}

void PBRMaterial::SetRoughness(Texture2D* roughness, int location)
{
	mRoughness = roughness;
	mBindingLocations["roughnessMap"] = location;
}

void PBRMaterial::SetAO(Texture2D* ao, int location)
{
	mAO = ao;
	mBindingLocations["aoMap"] = location;
}

void PBRMaterial::SetBRDF(Texture2D* brdf, int location)
{
	mBRDF = brdf;
	mBindingLocations["brdfLUT"] = location;
}

void PBRMaterial::SetIrradianceMap(Cubemap* irrMap, int location)
{
	mIrradiance = irrMap;
	mBindingLocations["irradianceMap"] = location;
}

void PBRMaterial::SetPrefilterMap(Cubemap* prefilter, int location)
{
	mPrefilter = prefilter;
	mBindingLocations["prefilterMap"] = location;
}

void PBRMaterial::SetEnvironmentMap(PBRPreComputation* precompute) {
	SetIrradianceMap(precompute->GetIrradianceMap(), 0);
	SetPrefilterMap(precompute->GetPrefilterMap(), 1);
	SetBRDF(precompute->GetBRDF(), 2);
}