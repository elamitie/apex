#include "application.h"
#include "input/keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/cache/MeshCache.h"

void Application::Init() {
    mCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    GetRenderer()->RegisterCamera(mCamera);

    mReflectShader = std::make_shared<Shader>();
    mReflectShader->SetDebug(true)
				  ->Attach("reflection_mapping.vert")
		          ->Attach("reflection_mapping.frag")
		          ->Link()
		          ->AddAttribs({
        "position", "normal", "texCoords"
    });

    mMesh = MeshCache::GetMesh("nanosuit_reflection/nanosuit.obj");

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

    // Translation
    mTransform = glm::translate(mTransform, glm::vec3(0.0f, -1.75f, 0.0f));
    // Rotation
    mTransform = glm::rotate(mTransform, glm::radians(ElapsedTime() * 50.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));
    // Scale
    mTransform = glm::scale(mTransform, glm::vec3(0.2f, 0.2f, 0.2f));

    GetRenderer()->PushMesh(mMesh, mReflectShader, mTransform);
}

void Application::Cleanup() {
    //delete mRenderer;
}