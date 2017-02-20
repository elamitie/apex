#include "camera.h"
#include <math.h>

Camera::Camera(glm::vec3 position, glm::vec3 up)
{
	Position = position;
	WorldUp = up;

	CalculateForward();
}

Camera::~Camera()
{
}

void Camera::HandleKeyboard(CameraDirection dir, float dt)
{
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

void Camera::HandleMouse(float xoff, float yoff, bool constrainPitch)
{
	xoff *= Properties.Sensitivity;
	yoff *= Properties.Sensitivity;

	Properties.Yaw += xoff;
	Properties.Pitch += yoff;

	if (constrainPitch)
	{
		if (Properties.Pitch > 89.0f)
			Properties.Pitch = 89.0f;
		if (Properties.Pitch < -89.0f)
			Properties.Pitch = -89.0f;
	}

	CalculateForward();
}

void Camera::HandleScroll(float yoff)
{
	if (Properties.Zoom >= 1.0f && Properties.Zoom <= 45.0f)
		Properties.Zoom -= yoff;
	if (Properties.Zoom <= 1.0f)
		Properties.Zoom = 1.0f;
	if (Properties.Zoom >= 45.0f)
		Properties.Zoom = 45.0f;
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::CalculateForward()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch));
	front.y = sin(glm::radians(Properties.Pitch));
	front.z = sin(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch));

	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
