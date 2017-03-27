#pragma once
#include "../../utils/Math.h"
#include "utils/Types.h"

// TODO: This maybe should have different subclasses for user controlled and auto fly.

enum CameraDirection {
    CamForward,
    CamBack,
    CamLeft,
    CamRight,
    CamUp,
    CamDown
};

// Default
struct CameraProperties {
    float Yaw         = -90.0f;
    float Pitch       =  0.0f;
    float Speed       =  3.0f;
    float Sensitivity =  0.25f;
    float Zoom        =  45.0f;
};

class Camera {
public:
    Camera(glm::vec3 pos = vec3_zero, glm::vec3 up = vec3_up);
    ~Camera();

    // TODO: Abstract these away into input management
    void HandleKeyboard(CameraDirection dir, float dt);
    void HandleMouse(float deltaX, float deltaY);

    glm::mat4 GetView();
    glm::mat4 CreateProjection(uint width, uint height);

public:
    CameraProperties Properties;
    // Should be private in the future?
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 CameraUp;
    glm::vec3 Right;
    glm::vec3 WorldUp;

private:
    void CalculateForward();
};