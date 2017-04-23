#include "application.h"
#include "input/keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/cache/MeshCache.h"

void Application::Init() {
	PBRScene* pbrScene = new PBRScene(GetWidth(), GetHeight());
	SetScene(pbrScene);
    SetColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
}

void Application::Update() {
    Engine::Update();
}

void Application::Render() {
	Engine::Render();
}

void Application::Cleanup() {
    //delete mRenderer;
}