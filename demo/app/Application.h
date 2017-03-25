#pragma once

#include "engine/Engine.h"
#include "graphics/assets/Shader.h"
#include "graphics/assets/Texture.h"
#include "graphics/view/Camera.h"
#include "graphics/mesh/Mesh.h"
#include "utils/Math.h"
#include "utils/Types.h"
#include "utils/Console.h"

// post process
#include "graphics/processing/postProcessor.h"

class Application : public Engine {
public:
    void Init() override;
    void Update() override;
    void Render() override;
    void Cleanup() override {};

private:
    ShaderPtr mMeshShader;
    ShaderPtr mHdrShader;
    MeshPtr mMesh;
    CameraPtr mCamera;

    glm::vec3 mLightPos;

    FrameBuffer* mFrameBuffer;
    PostProcessor* mPostProcessor;
};