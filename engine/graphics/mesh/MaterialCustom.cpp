#include "MaterialCustom.h"

void MaterialCustom::SetData()
{
	MaterialBase::SetData();

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

	// Set pre-defined textures
	for (auto& uniform : mBindingLocations) {
		mShader->SetUniform(uniform.first, uniform.second);
	}

	// TODO: We can set these elsewhere, technically - refactor this maybe?
	SetVector("albedo", glm::vec3(mAlbedo.r / 255.f, mAlbedo.g / 255.f, mAlbedo.b / 255.f));
	SetFloat("metallic", mMetallic);
	SetFloat("roughness", mRoughness);
	SetFloat("ao", mAO);
}

void MaterialCustom::SetAlbedo(Color& color)
{
	mAlbedo = color;
}

void MaterialCustom::SetMetallic(float metallic)
{
	mMetallic = metallic;
}

void MaterialCustom::SetRoughness(float roughness)
{
	mRoughness = roughness;
}

void MaterialCustom::SetAO(float ao)
{
	mAO = ao;
}