#include "postProcessor.h"

PostProcessor::PostProcessor() {

}

PostProcessor::~PostProcessor() {
    // TODO: MEMORY LEAKS LUL
}

void PostProcessor::Init() {
    glGenVertexArrays(1, &mQuadVao);
    glGenBuffers(1, &mQuadVbo);
    glBindVertexArray(mQuadVao);
    glBindBuffer(GL_ARRAY_BUFFER, mQuadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mQuadVertices), &mQuadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
}

void PostProcessor::Process(int texture) {
    Start();

    for (auto& pe : mEffects) {
        pe->PreRender();
        pe->Render(texture);
        pe->PostRender();
    }

    End();
}

void PostProcessor::PushEffect(ShaderPtr shader) {
    mEffects.push_back(new PostProcessEffect(shader));
}

void PostProcessor::Start() {
    glBindVertexArray(mQuadVao);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glDisable(GL_DEPTH_TEST);
}

void PostProcessor::End() {
    glEnable(GL_DEPTH_TEST);
    //glDisableVertexAttribArray(1);
    //glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}