#pragma once

#include "../utils/math.h"

class Mouse {
public:
    static void Clear();

    static void __hardwareMouseButtonPress();
    static void __hardwareMouseButtonRelease();
    static void __hardwareMouseMove();

private:
    glm::vec2 mPosition;

    bool mLeftDown, mLeftPressed, mLeftReleased;
    bool mRightDown, mRightPressed, mRightReleased;
};