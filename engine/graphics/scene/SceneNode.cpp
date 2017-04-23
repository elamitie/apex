#include "SceneNode.h"

glm::mat4& Transform::UpdateTransform() {
	glm::mat4 mat = glm::mat4();
	
	mat = glm::translate(mat, position);
	mat = glm::scale(mat, scale);
	glm::vec3 rot = glm::vec3(rotation.x, rotation.y, rotation.z);
	mat = glm::rotate(mat, glm::radians(rotation.w), rot);

	return mat;
}

void SceneNode::AddChild(SceneNodePtr node) {
	if (node->mParent) {
		node->mParent->RemoveChild(node->name);
	}

	node->mParent = shared_from_this();
	mChildren.push_back(node);
}

void SceneNode::RemoveChild(const std::string& name)
{
	auto it = std::find(mChildren.begin(), mChildren.end(), GetChild(name));
	if (it != mChildren.end()) {
		mChildren.erase(it);
	}
}

std::vector<SceneNodePtr> SceneNode::GetChildren()
{
	return mChildren;
}

int SceneNode::GetChildCount()
{
	return mChildren.size();
}

SceneNodePtr SceneNode::GetChild(const std::string& name)
{
	for (SceneNodePtr child : mChildren) {
		if (child->name == name) {
			return child;
		}
	}

	return nullptr;
}

SceneNodePtr SceneNode::GetParent()
{
	return mParent;
}

// I think there are better ways of doing this
glm::mat4& SceneNode::GetFinalTransform() {
	glm::mat4 t = transform.UpdateTransform();
	if (mParent) {
		t = mParent->GetFinalTransform() * t;
	}
	return t;
}