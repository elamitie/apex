#pragma once

#include "graphics/mesh/Mesh.h"
#include "graphics/assets/Shader.h"
#include "utils/Math.h"


struct RenderCommand {
    Mesh* mesh;
	Material* material;
    glm::mat4 transform;
};

typedef std::vector<RenderCommand> CommandBuffer;