#include "Scene.h"
#include "utils/Logger.h"

Scene::Scene(int width, int height) {
	mRenderer = new ForwardRenderer(width, height);
}

void Scene::Begin() {

}

void Scene::Update(double dt) {
	// @Todo: do thing, though leaving this up to child scenes is fine
	// Scene nodes don't necessarily need an update, this is a renderer
	// not a game engine
}

void Scene::Render(double dt) {
	mRenderer->Begin();
	mRenderer->PushNode(mRoot);
	mRenderer->End();
	mRenderer->Flush();
}

void Scene::End() {

}

SceneNodePtr Scene::CreateNode(const std::string& name) {
	SceneNodePtr node = std::make_shared<SceneNode>();
	// First evaluate whether the name is valid
	if (mRoot) {
		auto child = mRoot->GetChild(name);
		if (child == nullptr) {
			node->name = name;
			mRoot->AddChild(node);
			return node;
		} else {
			Logger::Log("Child with name already exists, not added to scene.", ERROR);
			return nullptr;
		}
	} else {
		// if mRoot doesn't exist, set it here!
		node->name = name;
		mRoot = node;
		
		return node;
	}
}

// Potentially design flaw, though it really doesn't matter? ->
// We have to create a node here, and then manually add the returned node
// to a different child if we want to do that.
SceneNodePtr Scene::CreateNode(Mesh* mesh, Material* material, const std::string& name) {
	SceneNodePtr node = std::make_shared<SceneNode>();
	
	if (mRoot) {
		auto child = mRoot->GetChild(name);
		if (child == nullptr) {
			node->name = name;
			node->mesh = mesh;
			node->material = material;
			mRoot->AddChild(node);
			return node;
		} else {
			Logger::Log("Child with name already exists, not added to scene.", ERROR);
			return nullptr;
		}
	} else {
		node->name = name;
		node->mesh = mesh;
		node->material = material;
		mRoot = node;

		return node;
	}
}

void Scene::DeleteNode(SceneNodePtr node) {
	if (node->GetParent()) {
		node->GetParent()->RemoveChild(node->name);
	}

	// deleting shared pointers question mark
	node = nullptr;
}

