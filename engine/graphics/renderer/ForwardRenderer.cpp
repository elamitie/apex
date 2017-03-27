#include "ForwardRenderer.h"
#include "utils/Logger.h"

ForwardRenderer::ForwardRenderer(uint width, uint height) {
    mWidth = width;
    mHeight = height;

    mDefaultPostEffect = std::make_shared<Shader>();
    mDefaultPostEffect->Attach("textured_quad.vert")->Attach("framebuffer_default.frag")->Link()->AddAttribs({
        "position", "texCoords"
    });

    mFramebuffer = std::make_shared<FrameBuffer>(mWidth, mHeight, DEPTH_RENDER_BUFFER, true);
    mPostProcessor = std::make_shared<PostProcessor>();
    mPostProcessor->Init();
    mPostProcessor->PushEffect(mDefaultPostEffect);

    mCommandBuffer.reserve(1000);
}

void ForwardRenderer::RegisterCamera(CameraPtr camera) {
    mCamera = camera;

    mProj = mCamera->CreateProjection(mWidth, mHeight);
}

void ForwardRenderer::Begin() {
    mView = mCamera->GetView();

    mCommandBuffer.clear();
    mFramebuffer->Bind();
}

void ForwardRenderer::PushMesh(MeshPtr mesh, ShaderPtr shader, glm::mat4 transform) {
    RenderCommand command;
    command.mesh = mesh;
    command.shader = shader;
    command.transform = transform;
    mCommandBuffer.push_back(command);
}

void ForwardRenderer::PushPostEffect(ShaderPtr shader) {
    mPostProcessor->PushEffect(shader);
}

void ForwardRenderer::End() {
    // TODO: Batching or sorting....?
}

void ForwardRenderer::Flush() {
    for (int i = 0; i < mCommandBuffer.size(); i++) {
        RenderCommand& command = mCommandBuffer[i];
        SetShaderUniforms(command);
        command.mesh->Render(command.shader);
    }

    mFramebuffer->Unbind();
    mPostProcessor->Process(mFramebuffer->GetColorTexture());
}

void ForwardRenderer::SetShaderUniforms(RenderCommand& command) {
    command.shader->Enable();
    command.shader->SetUniform("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    command.shader->SetUniform("viewPos", mCamera->Position);
    command.shader->SetUniform("lightAmbient", glm::vec3(0.4f, 0.4f, 0.4f));
    command.shader->SetUniform("lightDiffuse", glm::vec3(0.6f, 0.6f, 0.6f));
    command.shader->SetUniform("lightSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    command.shader->SetUniform("shininess", 32.0f);
    command.shader->SetUniform("view", mView);
    command.shader->SetUniform("projection", mProj);
    command.shader->SetUniform("model", command.transform);
}