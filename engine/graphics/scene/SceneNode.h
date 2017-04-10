#pragma once

#include "utils/Math.h"
#include "graphics/mesh/Mesh.h"

class Transform {
public:
	Transform() {
		// Set scale to one instead of 0 by default
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	};
	~Transform() {};

	glm::mat4& UpdateTransform();

	// Public vars
	glm::vec3 position;
	glm::vec4 rotation = glm::vec4(0.0, 1.0, 0.0, 0.0);		// Axis-angle, no quaternion (for now)
	glm::vec3 scale;
};

typedef std::enable_shared_from_this<SceneNode> SceneNodeShared;

class SceneNode : public SceneNodeShared {
public:
	SceneNode() {};
	~SceneNode() {};

	void AddChild(SceneNodePtr node);
	void RemoveChild(const std::string& name);

	std::vector<SceneNodePtr> GetChildren();
	int GetChildCount();

	SceneNodePtr GetChild(const std::string& name);
	SceneNodePtr GetParent();

	glm::mat4& GetFinalTransform();

	// Public vars
	Mesh* mesh;
	Material* material;
	Transform transform;

	// Dunno if I want this public or not
	std::string name;

private:
	std::vector<SceneNodePtr> mChildren;
	SceneNodePtr mParent;
};