#include "transform.h"

Transform::Transform()
{
	// set the model to identity
	mModelMatrix = glm::mat4();


}

Transform::~Transform()
{

}

void Transform::translate(const glm::vec3& translation)
{

}

void Transform::scale(const glm::vec3& scale)
{

}

void Transform::rotate(const glm::vec3& rotation)
{

}

glm::vec3 Transform::getPosition()
{
	return glm::vec3();
}

glm::vec3 Transform::getScale()
{
	return glm::vec3();
}

glm::vec3 Transform::getRotation()
{
	return glm::vec3();
}