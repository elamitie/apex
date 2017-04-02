#pragma once

#include "graphics/view/Camera.h"
#include "RenderCommand.h"
#include "graphics/processing/PostProcessor.h"
#include "graphics/view/Skybox.h"
#include "graphics/scene/SceneNode.h"

// TODO: PUSH LIGHTS

enum LightMode {
	PHONG,
	PBR
};

class ForwardRenderer {
public:
    ForwardRenderer(uint width, uint height);

    void Begin();
    void PushMesh(Mesh* mesh, Material* material, glm::mat4 transform);
	void PushNode(SceneNodePtr node);

    // TODO: This needs to be more robust to handle things like two-step gaussian
    void PushPostEffect(ShaderPtr shader);
    void End();
    void Flush();

    void RegisterCamera(CameraPtr camera);

	void SetLightingMode(LightMode mode);

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
    ShaderPtr mDefaultPostEffect;
    FrameBufferPtr mFramebuffer;
    PostProcessorPtr mPostProcessor;
    CommandBuffer mCommandBuffer;
    SkyboxPtr mSkybox;
};