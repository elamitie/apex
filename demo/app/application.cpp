#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });

	mLightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	mLightingShader = new Shader("../resources/shaders/mat_lighting.vert", "../resources/shaders/mat_lighting.frag");
	mLightingShader->AddAttribute("position");
	mLightingShader->AddAttribute("normal");

	mLampShader = new Shader("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	mLampShader->AddAttribute("position");

	mTexture = new Texture2D();
	mTexture->Load("../resources/textures/bricks.jpg");

	SetClearColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
	
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(mVao);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &mLightVao);
	glBindVertexArray(mLightVao);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
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
	mLightingShader->Bind();

	glm::vec3 lightColor;
	lightColor.x = sin(ElapsedTime() * 2.0f);
	lightColor.y = sin(ElapsedTime() * 0.7f);
	lightColor.z = sin(ElapsedTime() * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	mLightingShader->SetUniform("viewPos", mCamera->Position);
	mLightingShader->SetUniform("light.position", mLightPos);

	mLightingShader->SetUniform("light.ambient", ambientColor);
	mLightingShader->SetUniform("light.diffuse", diffuseColor);
	mLightingShader->SetUniform("light.specular", glm::vec3(1.0f));

	mLightingShader->SetUniform("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	mLightingShader->SetUniform("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	mLightingShader->SetUniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	mLightingShader->SetUniform("material.shininess", 32.0f);

	glm::mat4 view;
	view = mCamera->GetView();
	glm::mat4 proj = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	mLightingShader->SetUniform("view", view);
	mLightingShader->SetUniform("projection", proj);

	glBindVertexArray(mVao);
	glm::mat4 model;
	model = glm::rotate(model, (float)glm::radians(ElapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mLightingShader->SetUniform("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	mLampShader->Bind();
	mLampShader->SetUniform("view", view);
	mLampShader->SetUniform("projection", proj);
	
	mLightPos.x = std::cos(ElapsedTime());
	mLightPos.y = std::sin(ElapsedTime() * 2.0f);
	mLightPos.z = std::sin(ElapsedTime());

	model = glm::mat4();
	model = glm::translate(model, mLightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	mLampShader->SetUniform("model", model);

	glBindVertexArray(mLightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Application::Cleanup()
{
	delete mTexture;
	//delete mShader;
	delete mCamera;
}
