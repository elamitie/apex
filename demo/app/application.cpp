#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });

	mLightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	mLightingShader = new Shader("../resources/shaders/textured_mat_lighting.vert", "../resources/shaders/textured_mat_lighting.frag");
	mLightingShader->AddAttribute("position");
	mLightingShader->AddAttribute("normal");
	mLightingShader->AddAttribute("texCoords");

	mLampShader = new Shader("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	mLampShader->AddAttribute("position");

	mDiffuse = new Texture2D();
	mDiffuse->Load("../resources/textures/container2.png");
	mSpecular = new Texture2D();
	mSpecular->Load("../resources/textures/container2_specular.png");

	SetClearColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
	
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(mVao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &mLightVao);
	glBindVertexArray(mLightVao);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
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

	mLightingShader->SetUniform("viewPos", mCamera->Position);
	mLightingShader->SetUniform("light.position", mLightPos);

	mLightingShader->SetUniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	mLightingShader->SetUniform("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	mLightingShader->SetUniform("light.specular", glm::vec3(1.0f));

	mLightingShader->SetUniform("material.diffuse", 0);
	mLightingShader->SetUniform("material.specular", 1);
	mLightingShader->SetUniform("material.shininess", 32.0f);

	glm::mat4 view;
	view = mCamera->GetView();
	glm::mat4 proj = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	mLightingShader->SetUniform("view", view);
	mLightingShader->SetUniform("projection", proj);

	mDiffuse->Bind(0);
	mSpecular->Bind(1);
	glBindVertexArray(mVao);
	glm::mat4 model;
	model = glm::rotate(model, (float)glm::radians(ElapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mLightingShader->SetUniform("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	mSpecular->Unbind();
	mDiffuse->Unbind();

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
	delete mDiffuse;
	//delete mShader;
	delete mCamera;
}
