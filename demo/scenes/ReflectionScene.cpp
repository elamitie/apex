#include "ReflectionScene.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/cache/MeshCache.h"

void ReflectionScene::Begin()
{
	Scene::Begin();

	camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	mRenderer->SetLightingMode(PHONG);
	mRenderer->RegisterCamera(camera);

	reflection = new ReflectionMaterial();
	reflection->SetCamera(camera);
	sphereMesh = new Sphere(64, 64);

	sphere = CreateNode(sphereMesh, reflection, "sphere");
	sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
}

void ReflectionScene::Update(double dt)
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

void ReflectionScene::End()
{
	delete sphereMesh;
	delete reflection;

	Scene::End();
}
