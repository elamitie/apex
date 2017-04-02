#include "PBRScene.h"
#include "input/Keyboard.h"
#include "graphics/mesh/cache/MeshCache.h"

void PBRScene::Begin()
{
	Scene::Begin();

	camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	mRenderer->RegisterCamera(camera);

	reflection = std::make_shared<Shader>();
	reflection->SetDebug(false)
		->Attach("reflection_mapping.vert")
		->Attach("reflection_mapping.frag")
		->Link()
		->AddAttribs({
		"position", "normal", "texCoords"
	});

	MeshPtr mesh = MeshCache::GetMesh("nanosuit_reflection/nanosuit.obj");

	nanosuit = CreateNode(mesh, reflection, "nanosuit");
	nanosuit->transform.position = glm::vec3(0.0f, -1.75f, 0.0f);
	nanosuit->transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
}

void PBRScene::Update(double dt)
{
	Scene::Update(dt);

	if (Keyboard::KeyDown(GLFW_KEY_W))
		camera->HandleKeyboard(CamForward, dt);
	if (Keyboard::KeyDown(GLFW_KEY_S))
		camera->HandleKeyboard(CamBack, dt);
	if (Keyboard::KeyDown(GLFW_KEY_A))
		camera->HandleKeyboard(CamLeft, dt);
	if (Keyboard::KeyDown(GLFW_KEY_D))
		camera->HandleKeyboard(CamRight, dt);
}

void PBRScene::End()
{
	Scene::End();
}
