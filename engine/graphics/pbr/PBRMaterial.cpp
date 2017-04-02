#include "PBRMaterial.h"

PBRMaterial::PBRMaterial() {

}

void PBRMaterial::SetData() {
	// Set all of this shader's uniforms
	// @TODO: Take in a vector of PointLights! These are hardcoded for now!
	
	if (mIrradiance) mIrradiance->Bind(mBindingLocations["irradianceMap"]);
	if (mPrefilter) mPrefilter->Bind(mBindingLocations["prefilterMap"]);
	if (mBDRF) mBDRF->Bind(mBindingLocations["bdrfLUT"]);
	if (mAlbedo) mAlbedo->Bind(mBindingLocations["albedo"]);
	if (mNormal) mNormal->Bind(mBindingLocations["normal"]);
	if (mMetallic) mMetallic->Bind(mBindingLocations["metallic"]);
	if (mRoughness) mRoughness->Bind(mBindingLocations["roughness"]);
	if (mAO) mAO->Bind(mBindingLocations["ao"]);
}

void PBRMaterial::SetAlbedo(TexturePtr albedo, int location)
{
	mAlbedo = albedo;
	mShader->SetUniform("albedo", location);
	mBindingLocations["albedo"] = location;
}

void PBRMaterial::SetNormal(TexturePtr normal, int location)
{
	mNormal = normal;
	mShader->SetUniform("normal", location);
	mBindingLocations["normal"] = location;
}

void PBRMaterial::SetMetallic(TexturePtr metallic, int location)
{
	mMetallic = metallic;
	mShader->SetUniform("metallic", location);
	mBindingLocations["metallic"] = location;
}

void PBRMaterial::SetRoughness(TexturePtr roughness, int location)
{
	mRoughness = roughness;
	mShader->SetUniform("roughness", location);
	mBindingLocations["roughness"] = location;
}

void PBRMaterial::SetAO(TexturePtr ao, int location)
{
	mAO = ao;
	mShader->SetUniform("ao", location);
	mBindingLocations["ao"] = location;
}

void PBRMaterial::SetBDRF(TexturePtr bdrf, int location)
{
	mBDRF = bdrf;
	mShader->SetUniform("bdrfLUT", location);
	mBindingLocations["bdrfLUT"] = location;
}

void PBRMaterial::SetIrradianceMap(CubemapPtr irrMap, int location)
{
	mIrradiance = irrMap;
	mShader->SetUniform("irradianceMap", location);
	mBindingLocations["irradianceMap"] = location;
}

void PBRMaterial::SetPrefilterMap(CubemapPtr prefilter, int location)
{
	mPrefilter = prefilter;
	mShader->SetUniform("prefilterMap", location);
	mBindingLocations["prefilterMap"] = location;
}