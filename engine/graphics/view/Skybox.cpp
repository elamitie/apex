#include "Skybox.h"

Skybox::Skybox() {

    mSkyboxShader = std::make_shared<Shader>();
    mSkyboxShader->Attach("skybox.vert")->Attach("skybox.frag")->Link()->AddAttribs({
        "position"
    });

    mCubemap = new Cubemap();
    mCubemap->Load({
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "back.jpg",
        "front.jpg"
    });

    glGenVertexArrays(1, &mVertexArray);
    glGenBuffers(1, &mVertexBuffer);
    glBindVertexArray(mVertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVerts), &mVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
}

Skybox::~Skybox() {
    delete mCubemap;
}

void Skybox::Render(const glm::mat4& view, const glm::mat4& proj) {
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    mSkyboxShader->Enable();

    glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

    mSkyboxShader->SetUniform("view", skyboxView);
    mSkyboxShader->SetUniform("projection", proj);

    glBindVertexArray(mVertexArray);
    mCubemap->Bind(4);
    mSkyboxShader->SetUniform("skybox", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
    //glDepthMask(GL_TRUE);
}