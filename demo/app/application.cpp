#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });

	mMeshShader = std::make_shared<Shader>("../resources/shaders/model_loading_demo.vert", "../resources/shaders/model_loading_demo.frag");
	mMeshShader->AddAttribute("position");
	mMeshShader->AddAttribute("normal");
	mMeshShader->AddAttribute("texCoords");

	mMesh = std::make_shared<Mesh>("../resources/models/nanosuit/nanosuit.obj");

	SetClearColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
}

void Application::Update()
{
	if (Keyboard::KeyDown(GLFW_KEY_W))
		mCamera->HandleKeyboard(CamForward, DeltaTime());
	if (Keyboard::KeyDown(GLFW_KEY_S))
		mCamera->HandleKeyboard(CamBack, DeltaTime());
	if (Keyboard::KeyDown(GLFW_KEY_A))
		mCamera->HandleKeyboard(CamLeft, DeltaTime());
	if (Keyboard::KeyDown(GLFW_KEY_D))
		mCamera->HandleKeyboard(CamRight, DeltaTime());
}

void Application::Render()
{
	mMeshShader->Bind();

	glm::mat4 view;
	view = mCamera->GetView();
	glm::mat4 proj = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	mMeshShader->SetUniform("view", view);
	mMeshShader->SetUniform("projection", proj);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	mMeshShader->SetUniform("model", model);

	mMesh->Render(mMeshShader);
}

void Application::Cleanup()
{
	delete mCamera;
}
