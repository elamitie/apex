#include "application.h"
#include "input/keyboard.h"
#include "input/Mouse.h"

void Application::Init() {
    mCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    GetRenderer()->RegisterCamera(mCamera);

    mMeshReflectiveShader = std::make_shared<Shader>();
    mMeshRefractiveShader = std::make_shared<Shader>();
    /*mMeshShader->Attach("normal_mapping.vert")->Attach("normal_mapping.frag")->Link()->AddAttribs({
        "position", "normal", "texCoords", "tangents", "bitangents"
    });*/
    mMeshReflectiveShader->Attach("env_reflection.vert")->Attach("env_reflection.frag")->Link()->AddAttribs({
        "position", "normal"
    });
    mMeshRefractiveShader->Attach("env_refraction.vert")->Attach("env_refraction.frag")->Link()->AddAttribs({
        "position", "normal"
    });

    mMeshReflective = std::make_shared<Mesh>("nanosuit/nanosuit.obj");
    mMeshRefractive = std::make_shared<Mesh>("nanosuit/nanosuit.obj");

    // TODO: Figure out why the fuck Sponza isn't showing textures properly
    //mMesh = std::make_shared<Mesh>("sponza/sponza.obj");

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

    mCamera->HandleMouse(Mouse::XOffset, Mouse::YOffset);
}

void Application::Render() {
    mMeshReflectiveTransform = mMeshRefractiveTransform = glm::mat4();
    //mTransform = glm::rotate(mTransform, glm::radians(ElapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mMeshReflectiveTransform = glm::translate(mMeshReflectiveTransform, glm::vec3(2.0f, -1.75f, 0.0f));
    mMeshReflectiveTransform = glm::scale(mMeshReflectiveTransform, glm::vec3(0.2f, 0.2f, 0.2f));
    mMeshRefractiveTransform = glm::translate(mMeshRefractiveTransform, glm::vec3(-2.0f, -1.75f, 0.0f));
    mMeshRefractiveTransform = glm::scale(mMeshRefractiveTransform, glm::vec3(0.2f, 0.2f, 0.2f));

    GetRenderer()->PushMesh(mMeshReflective, mMeshReflectiveShader, mMeshReflectiveTransform);
    GetRenderer()->PushMesh(mMeshRefractive, mMeshRefractiveShader, mMeshRefractiveTransform);
}

void Application::Cleanup() {
    //delete mRenderer;
}