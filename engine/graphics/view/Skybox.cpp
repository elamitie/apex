#include "Skybox.h"

Skybox::Skybox(const std::string& vert, const std::string& frag) {

	mSkyboxShader = new Shader();
    mSkyboxShader->Attach(vert)->Attach(frag)->Link()->AddAttribs({
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

    mSkyboxShader->SetUniform("view", view);
    mSkyboxShader->SetUniform("projection", proj);

    glBindVertexArray(mVertexArray);
    mCubemap->Bind(0);
    mSkyboxShader->SetUniform("environmentMap", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
    //glDepthMask(GL_TRUE);
}