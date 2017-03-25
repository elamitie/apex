#include "Keyboard.h"

bool* Keyboard::mDown = new bool[1024];
bool* Keyboard::mNext = new bool[1024];
bool* Keyboard::mLast = new bool[1024];

void Keyboard::init() {
    for (int i = 0; i < 1024; i++) {
        mDown[i] = false;
        mNext[i] = false;
        mLast[i] = false;
    }
}

void Keyboard::update() {
    for (int i = 0; i < 1024; i++) {
        Keyboard::mLast[i] = Keyboard::mDown[i];
        Keyboard::mDown[i] = Keyboard::mNext[i];
    }
}

void Keyboard::cleanup() {
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

bool Keyboard::keyDown(int key) {
    return (Keyboard::mDown[key]);
}

bool Keyboard::keyPressed(int key) {
    return (Keyboard::mDown[key] && !Keyboard::mLast[key]);
}

bool Keyboard::keyReleased(int key) {
    return (!Keyboard::mDown[key] && Keyboard::mLast[key]);
}
