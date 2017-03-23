#include "camera.h"
#include <math.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up) {
    position = pos;
    worldUp = up;

    calculateForward();
}

Camera::~Camera() {
}

void Camera::handleKeyboard(CameraDirection dir, float dt) {
    float vel = properties.speed * dt;
    if (dir == CamForward)
        position += front * vel;
    if (dir == CamBack)
        position -= front * vel;
    if (dir == CamLeft)
        position -= right * vel;
    if (dir == CamRight)
        position += right * vel;
}

void Camera::handleMouse(float xoff, float yoff, bool constrainPitch) {
    xoff *= properties.sensitivity;
    yoff *= properties.sensitivity;

    properties.yaw += xoff;
    properties.pitch += yoff;

    if (constrainPitch) {
        if (properties.pitch > 89.0f)
            properties.pitch = 89.0f;
        if (properties.pitch < -89.0f)
            properties.pitch = -89.0f;
    }

    calculateForward();
}

void Camera::handleScroll(float yoff) {
    if (properties.zoom >= 1.0f && properties.zoom <= 45.0f)
        properties.zoom -= yoff;
    if (properties.zoom <= 1.0f)
        properties.zoom = 1.0f;
    if (properties.zoom >= 45.0f)
        properties.zoom = 45.0f;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(position, position + front, cameraUp);
}

void Camera::calculateForward() {
    glm::vec3 f;
    f.x = cos(glm::radians(properties.yaw)) * cos(glm::radians(properties.pitch));
    f.y = sin(glm::radians(properties.pitch));
    f.z = sin(glm::radians(properties.yaw)) * cos(glm::radians(properties.pitch));

    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, worldUp));
    cameraUp = glm::normalize(glm::cross(right, front));
}
