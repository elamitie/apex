#include "PBRScene.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/prefab/Sphere.h"
#include "utils/Logger.h"

#include "graphics/assets/cache/TextureCache.h"

void PBRScene::Begin()
{
	Scene::Begin();

	camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	mRenderer->SetLightingMode(PBR);
	mRenderer->RegisterCamera(camera);

	pbr = new Shader();
	pbr->SetDebug(true);
	pbr->Attach("pbr/pbr.vert")->Attach("pbr/pbr.frag")->Link();
	pbr->AddAttribs({ "position", "normal", "texCoords" });

	pbrCustom = new Shader();
	pbrCustom->SetDebug(true);
	pbrCustom->Attach("pbr/pbr_custom.vert")->Attach("pbr/pbr_custom.frag")->Link();
	pbrCustom->AddAttribs({ "position", "normal", "texCoords" });

	plastic = new Material();
	plastic->SetCamera(camera);
	plastic->SetShader(pbr);
	plastic->SetAlbedo(TextureCache::GetTexture("pbr/plastic/albedo.png"), 3);
	plastic->SetNormal(TextureCache::GetTexture("pbr/plastic/normal.png"), 4);
	plastic->SetMetallic(TextureCache::GetTexture("pbr/plastic/metallic.png"), 5);
	plastic->SetRoughness(TextureCache::GetTexture("pbr/plastic/roughness.png"), 6);
	plastic->SetAO(TextureCache::GetTexture("pbr/plastic/ao.png"), 7);

	gold = new Material();
	gold->SetCamera(camera);
	gold->SetShader(pbr);
	gold->SetAlbedo(TextureCache::GetTexture("pbr/gold/albedo.png"), 3);
	gold->SetNormal(TextureCache::GetTexture("pbr/gold/normal.png"), 4);
	gold->SetMetallic(TextureCache::GetTexture("pbr/gold/metallic.png"), 5);
	gold->SetRoughness(TextureCache::GetTexture("pbr/gold/roughness.png"), 6);
	gold->SetAO(TextureCache::GetTexture("pbr/gold/ao.png"), 7);

	custom = new MaterialCustom();
	custom->SetCamera(camera);
	custom->SetShader(pbrCustom);
	custom->SetAlbedo(Color(0, 200, 0));
	custom->SetMetallic(0.9f);
	custom->SetRoughness(0.1f);
	custom->SetAO(0.9f);

	mRenderer->RegisterCustomMaterial(custom);

	sphereMesh = new Sphere(64, 64);

	sphere = CreateNode(sphereMesh, plastic, "sphere");
	sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);

	targetRotation = sphere->transform.rotation.w;
}

void PBRScene::Update(double dt)
{
	Scene::Update(dt);

	camera->Update(dt);

	if (Keyboard::KeyDown(GLFW_KEY_A)) {
		targetRotation = sphere->transform.rotation.w += -50 * dt;
	}
	if (Keyboard::KeyDown(GLFW_KEY_D)) {
		targetRotation = sphere->transform.rotation.w += 50 * dt;
	}

	sphere->transform.rotation.w = math::Lerp(sphere->transform.rotation.w, targetRotation, dt * 5.0f);

	//camera->Position.x = std::cos(fuck) * camera->Position.z;
	//camera->Position.z = std::sin(fuck) * camera->Position.z;
}

void PBRScene::End()
{
	Scene::End();
}

void PBRScene::OnChangeMaterial(const std::string& matName) {
	Logger::Log("Changing Material: " + matName);

	DeleteNode(sphere);

	if (matName == "plastic") {
		sphere = CreateNode(sphereMesh, plastic, "sphere");
		sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	}
	else if (matName == "gold") {
		sphere = CreateNode(sphereMesh, gold, "sphere");
		sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	}
	else if (matName == "custom") {
		sphere = CreateNode(sphereMesh, custom, "sphere");
		sphere->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	}
}
