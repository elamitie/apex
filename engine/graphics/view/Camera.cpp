#include "Camera.h"
#include <math.h>
#include "utils/Math.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"

#include "utils/Logger.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up) {
    Position = pos;
	mTargetPosition = pos;
    WorldUp = up;

	mScrollDirty = false;

    CalculateForward();
}

Camera::~Camera() {
}

void Camera::HandleKeyboard(CameraDirection dir, float dt) {
    float vel = Properties.Speed * dt;
    if (dir == CamForward)
        Position += Front * vel;
    if (dir == CamBack)
        Position -= Front * vel;
    if (dir == CamLeft)
        Position -= Right * vel;
    if (dir == CamRight)
        Position += Right * vel;
}

void Camera::HandleMouse(float deltaX, float deltaY) {
    float xmovement = deltaX * Properties.Sensitivity;
    float ymovement = deltaY * Properties.Sensitivity;

    Properties.Yaw   += xmovement;
    Properties.Pitch += ymovement;

    if (Properties.Yaw   == 0.0f) Properties.Yaw   = 0.01f;
    if (Properties.Pitch == 0.0f) Properties.Pitch = 0.01f;

    if (Properties.Pitch >  89.0f)  Properties.Pitch =  89.0f;
    if (Properties.Pitch < -89.0f)  Properties.Pitch = -89.0f;

    CalculateForward();
}

void Camera::Update(double dt) {

	// "Zoom" in / out with the scroll wheel
	float vel = Properties.Speed * dt;
	if (Mouse::GetScrollOffset().y != mPreviousScroll.y) {
		mScrollDirty = true;
	}

	// Only move
	if (mScrollDirty) {

		mTargetPosition += Front * (Mouse::GetScrollOffset().y * 0.3f);
		mScrollDirty = false;
	}

	Position = math::Lerp(Position, mTargetPosition, math::Clamp01(dt * DampCoeff));

	if (Mouse::GetScrollOffset().y > 0 || Mouse::GetScrollOffset().y < 0) {
		mPreviousScroll = Mouse::GetScrollOffset();
	}

	CalculateForward();
}

glm::mat4 Camera::GetView() {
    return glm::lookAt(Position, Position + Front, CameraUp);
}

glm::mat4 Camera::CreateProjection(uint width, uint height) {
    return glm::perspective(Properties.Zoom, (float)width / (float)height, 0.1f, 100.0f);
}

void Camera::CalculateForward() {
    glm::vec3 f;
    f.x = cos(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch));
    f.y = sin(glm::radians(Properties.Pitch));
    f.z = sin(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch));

    Front = glm::normalize(f);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    CameraUp = glm::normalize(glm::cross(Right, Front));
}