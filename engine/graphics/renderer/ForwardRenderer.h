#pragma once

#include "graphics/view/Camera.h"
#include "RenderCommand.h"
#include "graphics/processing/PostProcessor.h"
#include "graphics/view/Skybox.h"
#include "graphics/scene/SceneNode.h"
#include "graphics/pbr/PBRPreComputation.h"
#include "graphics/mesh/MaterialCustom.h"

// TODO: PUSH LIGHTS

struct CustomMaterialTweaks
{
	Color* albedo;
	float* metallic;
	float* roughness;
	float* ao;
};

enum LightMode {
	PHONG,
	PBR
};

class ForwardRenderer {
public:
    ForwardRenderer(uint width, uint height, Scene* mParentScene);

    void Begin();
    void PushMesh(Mesh* mesh, MaterialBase* material, glm::mat4 transform);
	void PushNode(SceneNodePtr node);

    // TODO: This needs to be more robust to handle things like two-step gaussian
    void PushPostEffect(ShaderPtr shader);
    void End();
    void Flush();

    void RegisterCamera(CameraPtr camera);

	void SetLightingMode(LightMode mode);
	void ChangeEnvironment(const std::string& envName);

	void RegisterCustomMaterial(MaterialCustom* mat);

	void Interface();
	inline void SetDebug(bool debug) { mDebugMode = debug; }

private:
    void SetSystemUniforms(RenderCommand& command);

private:
    uint mWidth, mHeight;
	bool mDebugMode;
    glm::mat4 mView;
    glm::mat4 mProj;
    CameraPtr mCamera;
    CommandBuffer mCommandBuffer;
    SkyboxPtr mSkybox;
	PBRPreComputation* mPBRPreComputation;

	Scene* mParentScene;

	LightMode mMode;

	bool mTweakSliders = false;		// Tweak material values
	MaterialCustom* mCustomMat;		// Current registered custom material, currently only one supported at a time
};