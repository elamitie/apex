#pragma once

#include "graphics/mesh/Mesh.h"
#include "graphics/assets/Shader.h"
#include "utils/Math.h"


struct RenderCommand {
    MeshPtr mesh;
    ShaderPtr shader;
    glm::mat4 transform;
};

typedef std::vector<RenderCommand> CommandBuffer;