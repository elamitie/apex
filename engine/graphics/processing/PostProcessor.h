#pragma once

#include "postProcessEffect.h"
#include <vector>

class PostProcessor {
public:
    PostProcessor();
    ~PostProcessor();

    void init();
    void process(int texture);
    void pushEffect(ShaderPtr shader);

private:
    void start();
    void end();

private:
    std::vector<PostProcessEffect*> mEffects;

    // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    GLfloat mQuadVertices[24] = {
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    GLuint mQuadVao, mQuadVbo;
};