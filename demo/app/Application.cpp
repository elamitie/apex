#include "application.h"
#include "input/keyboard.h"
#include "input/Mouse.h"
#include "graphics/mesh/cache/MeshCache.h"

void Application::Init() {
	ReflectionScene* scene = new ReflectionScene(GetWidth(), GetHeight());
	SetScene(scene);
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