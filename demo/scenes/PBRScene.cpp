#include "PBRScene.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/prefab/Sphere.h"

void PBRScene::Begin()
{
	Scene::Begin();

	camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	mRenderer->SetLightingMode(PBR);
	mRenderer->RegisterCamera(camera);

	plasticAlbedo = new Texture2D();
	plasticAlbedo->Load(FileSystem::GetPath("resources/textures/pbr/gold/albedo.png"));
	plasticNormal = new Texture2D();
	plasticNormal->Load(FileSystem::GetPath("resources/textures/pbr/gold/normal.png"));
	plasticMetallic = new Texture2D();
	plasticMetallic->Load(FileSystem::GetPath("resources/textures/pbr/gold/metallic.png"));
	plasticRoughness = new Texture2D();
	plasticRoughness->Load(FileSystem::GetPath("resources/textures/pbr/gold/roughness.png"));
	plasticAO = new Texture2D();
	plasticAO->Load(FileSystem::GetPath("resources/textures/pbr/gold/ao.png"));

	plastic = new PBRMaterial();
	plastic->SetCamera(camera);
	plastic->SetAlbedo(plasticAlbedo, 3);
	plastic->SetNormal(plasticNormal, 4);
	plastic->SetMetallic(plasticMetallic, 5);
	plastic->SetRoughness(plasticRoughness, 6);
	plastic->SetAO(plasticAO, 7);

	sphereMesh = new Sphere(64, 64);

	sphere = CreateNode(sphereMesh, plastic, "sphere");
	sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
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

	camera->HandleMouse(Mouse::XOffset, Mouse::YOffset);
}

void PBRScene::End()
{
	Scene::End();
}
