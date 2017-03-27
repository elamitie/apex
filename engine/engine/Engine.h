#pragma once

#include "graphics/Window.h"
#include "utils/Console.h"
#include "utils/Logger.h"
#include "graphics/renderer/ForwardRenderer.h"

class Engine {
public:
    Engine() : mQuit (false) {}
    ~Engine() {}

    void Start(int width = 640, int height = 480,
               const char* title = "");
    void Quit();

    void SetTitle(const char* title);
    void SetDimensions(int width, int height);

    int GetWidth() { return mWindow->GetWidth(); }
    int GetHeight() { return mWindow->GetHeight(); }

    float DeltaTime() { return mDeltaTime; }
    float ElapsedTime() { return mTotalTime; }

    Console* GetConsole() { return mConsole; }
    ForwardRenderer* GetRenderer() { return mRenderer; }

    void SetColor (Color color);

protected:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void Update();
    virtual void Render();

private:
    void Loop();
    void InitBackend(int width, int height, const char* title);
    void CleanupBackend();

private:
    Window* mWindow;
    Console* mConsole;
    ForwardRenderer* mRenderer;

    bool mQuit;
    int mWidth, mHeight;

    float mDeltaTime;
    float mTotalTime;
};