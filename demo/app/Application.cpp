#include "application.h"
#include "input/keyboard.h"

void Application::Init() {
    mCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    mMeshShader = std::make_shared<Shader>();
    mMeshShader->Attach("prototype1_lighting.vert")->Attach("prototype1_lighting.frag")->Link()->AddAttribs({
        "position", "normal", "texCoords"
    });

    mHdrShader = std::make_shared<Shader>();
    mHdrShader->Attach("textured_quad.vert")->Attach("framebuffer_default.frag")->Link()->AddAttribs({
        "position", "texCoords"
    });

    mMesh = std::make_shared<Mesh>("nanosuit/nanosuit.obj");

    mLightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    mFrameBuffer = new FrameBuffer(GetWidth(), GetHeight(), DEPTH_RENDER_BUFFER, true);
    mPostProcessor = new PostProcessor();
    mPostProcessor->Init();
    mPostProcessor->PushEffect(mHdrShader);

    SetColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
}

void Application::Update() {
    Engine::Update();

    if (Keyboard::KeyDown(GLFW_KEY_W))
        mCamera->HandleKeyboard(CamForward, DeltaTime());
    if (Keyboard::KeyDown(GLFW_KEY_S))
        mCamera->HandleKeyboard(CamBack, DeltaTime());
    if (Keyboard::KeyDown(GLFW_KEY_A))
        mCamera->HandleKeyboard(CamLeft, DeltaTime());
    if (Keyboard::KeyDown(GLFW_KEY_D))
        mCamera->HandleKeyboard(CamRight, DeltaTime());
}

void Application::Render() {
    mMeshShader->Enable();

    mMeshShader->SetUniform("light.position", mLightPos);
    mMeshShader->SetUniform("viewPos", mCamera->Position);

    mMeshShader->SetUniform("light.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
    mMeshShader->SetUniform("light.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
    mMeshShader->SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    mMeshShader->SetUniform("material.shininess", 32.0f);

    glm::mat4 view;
    view = mCamera->GetView();
    glm::mat4 proj = glm::perspective(mCamera->Properties.Zoom,
                                      (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);


    mMeshShader->SetUniform("view", view);
    mMeshShader->SetUniform("projection", proj);

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(ElapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    mMeshShader->SetUniform("model", model);

    mFrameBuffer->Bind();
    mMesh->Render(mMeshShader);
    mFrameBuffer->Unbind();

    mPostProcessor->Process(mFrameBuffer->GetColorTexture());
}
