#include "application.h"
#include "input/keyboard.h"
#include "input/Mouse.h"

void Application::Init() {
    mCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    GetRenderer()->RegisterCamera(mCamera);

    mMeshShader = std::make_shared<Shader>();
    mMeshShader->Attach("normal_mapping.vert")->Attach("normal_mapping.frag")->Link()->AddAttribs({
        "position", "normal", "texCoords", "tangents", "bitangents"
    });

    // Note trying to normal map this looks like ass because of how they mirrored texture coordinates
    // on the object file.
    mMesh = std::make_shared<Mesh>("nanosuit/nanosuit.obj");

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
    mTransform = glm::mat4();
    //mTransform = glm::rotate(mTransform, glm::radians(ElapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mTransform = glm::translate(mTransform, glm::vec3(0.0f, -1.75f, 0.0f));
    mTransform = glm::scale(mTransform, glm::vec3(0.2f, 0.2f, 0.2f));

    GetRenderer()->PushMesh(mMesh, mMeshShader, mTransform);
}

void Application::Cleanup() {
    //delete mRenderer;
}