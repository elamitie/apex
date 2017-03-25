#include "Keyboard.h"

bool* Keyboard::mDown = new bool[1024];
bool* Keyboard::mNext = new bool[1024];
bool* Keyboard::mLast = new bool[1024];

void Keyboard::Init() {
    for (int i = 0; i < 1024; i++) {
        mDown[i] = false;
        mNext[i] = false;
        mLast[i] = false;
    }
}

void Keyboard::Update() {
    for (int i = 0; i < 1024; i++) {
        Keyboard::mLast[i] = Keyboard::mDown[i];
        Keyboard::mDown[i] = Keyboard::mNext[i];
    }
}

void Keyboard::Cleanup() {
    delete[] mDown;
    delete[] mNext;
    delete[] mLast;
}

void Keyboard::__hardwareKeyPress(int key) {
    Keyboard::mNext[key] = true;
}

void Keyboard::__hardwareKeyRelease(int key) {
    Keyboard::mNext[key] = false;
}

bool Keyboard::KeyDown(int key) {
    return (Keyboard::mDown[key]);
}

bool Keyboard::KeyPressed(int key) {
    return (Keyboard::mDown[key] && !Keyboard::mLast[key]);
}

bool Keyboard::KeyReleased(int key) {
    return (!Keyboard::mDown[key] && Keyboard::mLast[key]);
}
