#pragma once

#include "engine/engine.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"
#include "graphics/view/camera.h"
#include "graphics/mesh/mesh.h"
#include "utils/math.h"
#include "utils/types.h"
#include "utils/console.h"

class Application : public Engine
{
public:
    void init() override;
    void update() override;
    void render() override;
    void cleanup() override;

private:
    ShaderPtr mMeshShader;
    MeshPtr mMesh;
    CameraPtr mCamera;

    glm::vec3 mLightPos;
};