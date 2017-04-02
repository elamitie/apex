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
