#pragma once

#include "graphics/window.h"
#include "utils/console.h"
#include "utils/logger.h"

class Engine {
public:
    Engine() : mQuit (false) {}
    ~Engine() {}

    void start(int width = 640, int height = 480,
               const char* title = "");
    void quit();

    void setTitle(const char* title);
    void setDimensions(int width, int height);

    int getWidth() { return mWindow->getWidth(); }
    int getHeight() { return mWindow->getHeight(); }

    float deltaTime() { return mDeltaTime; }
    float elapsedTime() { return mTotalTime; }

    Console* console() { return mConsole; }

    void setColor (Color color);

protected:
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void update();
    virtual void render();

private:
    void loop();
    void initBackend(int width, int height, const char* title);
    void cleanupBackend();

private:
    Window* mWindow;
    Console* mConsole;

    bool mQuit;
    int mWidth, mHeight;

    float mDeltaTime;
    float mTotalTime;
};