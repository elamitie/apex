#pragma once
#include <GLFW/glfw3.h>

class Keyboard {
public:
    static void init();
    static void update();
    static void cleanup();

    static bool keyDown(int key);
    static bool keyReleased(int key);
    static bool keyPressed(int key);

    static void __hardwareKeyPress(int key);
    static void __hardwareKeyRelease(int key);

private:
    static bool* mDown;
    static bool* mLast;
    static bool* mNext;
};