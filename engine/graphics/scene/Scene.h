#pragma once

#include "SceneNode.h"
#include "graphics/renderer/ForwardRenderer.h"
#include <string>

class Scene {
public:
	// @Todo: passing in width and height to the scene seems weird, should
	// really just have some static reference to width and height of the app
	Scene(int width, int height);
	virtual ~Scene() { delete mRenderer; };

	virtual void Begin();
	virtual void Update(double dt);
	virtual void End();

	// Temporary for prototype 2's demo..?
	virtual void OnChangeMaterial(const std::string& matName) {};
	// -----------------------------------
	
	// Not overriden for now, no point.
	void Render(double dt);

	SceneNodePtr CreateNode(const std::string& name);
	SceneNodePtr CreateNode(Mesh* mesh, MaterialBase* material, const std::string& name);
	
	void DeleteNode(SceneNodePtr node);

protected:
	SceneNodePtr mRoot;

	// @Todo: Smart pointer
	ForwardRenderer* mRenderer;
};