#pragma once

#include "graphics/mesh/mesh.h"
#include "utils/math.h"

class Transform
{
public:
	Transform();
	~Transform();

	void translate(const glm::vec3& translation);
	void scale(const glm::vec3& scale);
	void rotate(const glm::vec3& rotation);

	// So the user can see data in a readable format
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getRotation();

private:
	// Model matrix, position scale and rotation are encoded already
	glm::mat4 mModelMatrix;

	// What object this transform belongs to
	SceneObjectPtr mSceneObject;

	// What scene this transform belongs to
	ScenePtr mScene;

	MeshPtr mMesh;
	ShaderPtr mShader;
};