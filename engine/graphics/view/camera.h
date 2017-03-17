#pragma once
#include "../../utils/math.h"

// TODO: This maybe should have different subclasses for user controlled and auto fly.

enum CameraDirection
{
    CamForward,
    CamBack,
    CamLeft,
    CamRight,
    CamUp,
    CamDown
};

// Default
struct CameraProperties
{
    float yaw         = -90.0f;
    float pitch       =  0.0f;
    float speed       =  3.0f;
    float sensitivity =  0.25f;
    float zoom        =  45.0f;
};

class Camera
{
public:
    Camera(glm::vec3 pos = vec3_zero, glm::vec3 up = vec3_up);
    ~Camera();

    // TODO: Abstract these away into input management
    void handleKeyboard(CameraDirection dir, float dt);
    void handleMouse(float xoff, float yoff, bool constrainPitch = true);
    void handleScroll(float yoff);

    glm::mat4 getView();

public:
    CameraProperties properties;
    // Should be private in the future?
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 cameraUp;
    glm::vec3 right;
    glm::vec3 worldUp;

private:
    void calculateForward();
};