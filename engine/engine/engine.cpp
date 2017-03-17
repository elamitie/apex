#include "engine.h"
#include "../input/keyboard.h"

void Engine::Start(int width, int height, const char* title)
{
    InitBackend(width, height, title);
    Init();

    Loop();

    Cleanup();
    CleanupBackend();
}

void Engine::Quit()
{
    // Not Implemented Yet
}

void Engine::SetTitle(const char* title)
{
    // Not Implemented Yet
}

void Engine::SetDimensions(int width, int height)
{
    // Not Implemented Yet
}

void Engine::SetClearColor(Color color)
{
    mWindow->SetClearColor(color);
}

void Engine::Loop()
{
    // TODO: More robust timing system
    float lastFrame = 0.0f;
    mDeltaTime = 0.0f;

    while (mWindow->Open())
    {
        // Accumulate total time
        mTotalTime = glfwGetTime();

        GLfloat currentFrame = glfwGetTime();
        mDeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        mWindow->Clear();

        Update();
        Render();

        mWindow->SwapBuffers();
    }
}

void Engine::InitBackend(int width, int height,
                         const char* title)
{
    mWidth = width;
    mHeight = height;
    mWindow = new Window(width, height, title);

    Keyboard::Init();
    mConsole = new Console();
    mConsole->Init(mWindow);
}

void Engine::CleanupBackend()
{
    Keyboard::CleanUp();
    delete mConsole;
    delete mWindow;
}

void Engine::Update()
{
    mWindow->Update();
}

void Engine::Render()
{
}