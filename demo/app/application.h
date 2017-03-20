#pragma once

#include "engine/engine.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"
#include "graphics/view/camera.h"
#include "graphics/mesh/mesh.h"
#include "utils/math.h"
#include "utils/types.h"
#include "utils/console.h"

// post process
#include "graphics/processing/postProcessor.h"

class Application : public Engine
{
public:
    void init() override;
    void update() override;
    void render() override;
    void cleanup() override;

private:
    ShaderPtr mMeshShader;
    ShaderPtr mHdrShader;
    MeshPtr mMesh;
    CameraPtr mCamera;

    glm::vec3 mLightPos;

    FrameBuffer* mFrameBuffer;
    PostProcessor* mPostProcessor;
};