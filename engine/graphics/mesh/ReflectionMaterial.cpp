#include "ReflectionMaterial.h"

ReflectionMaterial::ReflectionMaterial() {
	// Load default shader
	mShader = std::make_shared<Shader>();
	mShader->SetDebug(false)
		->Attach("env_reflection.vert")
		->Attach("env_reflection.frag")
		->Link()
		->AddAttribs({
		"position", "normal"
	});
}

void ReflectionMaterial::SetData() {
	if (mCamera) mShader->SetUniform("cameraPos", mCamera->Position);

	// Due to the nature of this material, this is wholey unecessary...
	if (mSkybox) mSkybox->GetCubemap()->Bind(mBindingLocations["skybox"]);
}

void ReflectionMaterial::SetSkybox(SkyboxPtr skybox) {
	if (!mSkybox) mSkybox = skybox;
	mBindingLocations["skybox"] = 0;
}
