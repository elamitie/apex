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

#include "../scenes/PBRScene.h"

class Application : public Engine {
public:
    void Init() override;
    void Update() override;
    void Render() override;
    void Cleanup() override;

};