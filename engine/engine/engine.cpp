#include "engine.h"
#include "../input/keyboard.h"

void Engine::start(int width, int height, const char* title)
{
    initBackend(width, height, title);
    init();

    loop();

    cleanup();
    cleanupBackend();
}

void Engine::quit()
{
    // Not Implemented Yet
}

void Engine::setTitle(const char* title)
{
    // Not Implemented Yet
}

void Engine::setDimensions(int width, int height)
{
    // Not Implemented Yet
}

void Engine::setColor(Color color)
{
    mWindow->setColor(color);
}

void Engine::loop()
{
    // TODO: More robust timing system
    float lastFrame = 0.0f;
    mDeltaTime = 0.0f;

    while (mWindow->open())
    {
        // Accumulate total time
        mTotalTime = glfwGetTime();

        GLfloat currentFrame = glfwGetTime();
        mDeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        mWindow->clear();

        update();
        render();

        mWindow->swapBuffers();
    }
}

void Engine::initBackend(int width, int height,
                         const char* title)
{
    mWidth = width;
    mHeight = height;
    mWindow = new Window(width, height, title);

    Keyboard::init();
    mConsole = new Console();
    mConsole->init(mWindow);
}

void Engine::cleanupBackend()
{
    Keyboard::cleanup();
    delete mConsole;
    delete mWindow;
}

void Engine::update()
{
    mWindow->update();
}

void Engine::render()
{
}