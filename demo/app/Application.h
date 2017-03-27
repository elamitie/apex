#pragma once

#include "engine/Engine.h"
#include "graphics/assets/Shader.h"
#include "graphics/assets/Texture.h"
#include "graphics/view/Camera.h"
#include "graphics/mesh/Mesh.h"
#include "utils/Math.h"
#include "utils/Types.h"
#include "utils/Console.h"
#include "graphics/renderer/ForwardRenderer.h"

// post process
#include "graphics/processing/postProcessor.h"

class Application : public Engine {
public:
    void Init() override;
    void Update() override;
    void Render() override;
    void Cleanup() override;

private:
    ShaderPtr mMeshReflectiveShader;
    ShaderPtr mMeshRefractiveShader;
    MeshPtr mMeshReflective;
    MeshPtr mMeshRefractive;
    glm::mat4 mMeshReflectiveTransform;
    glm::mat4 mMeshRefractiveTransform;
    CameraPtr mCamera;
};