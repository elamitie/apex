#pragma once
#include <GLFW/glfw3.h>

class Keyboard
{
public:
    static void Init();
    static void Update();
    static void CleanUp();

    static bool KeyDown(int key);
    static bool KeyReleased(int key);
    static bool KeyPressed(int key);

    static void __hardwareKeyPress(int key);
    static void __hardwareKeyRelease(int key);

private:
    static bool* mDown;
    static bool* mLast;
    static bool* mNext;
};