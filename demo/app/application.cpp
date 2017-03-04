#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });

	mLightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	mLightingShader = new Shader("../resources/shaders/lighting.vert", "../resources/shaders/lighting.frag");
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

	mLightingShader->SetUniform("material.diffuse", 0);
	mLightingShader->SetUniform("material.specular", 1);
	mLightingShader->SetUniform("material.shininess", 32.0f);

	mLightingShader->SetUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	mLightingShader->SetUniform("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	mLightingShader->SetUniform("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	mLightingShader->SetUniform("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	mLightingShader->SetUniform("pointLights[0].position",  pointLightPositions[0]);
	mLightingShader->SetUniform("pointLights[0].ambient",   glm::vec3(0.05f, 0.05f, 0.05f));
	mLightingShader->SetUniform("pointLights[0].diffuse",   glm::vec3(0.8f, 0.8f, 0.8f));
	mLightingShader->SetUniform("pointLights[0].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
	mLightingShader->SetUniform("pointLights[0].constant",  1.0f);
	mLightingShader->SetUniform("pointLights[0].linear",    0.09f);
	mLightingShader->SetUniform("pointLights[0].quadratic", 0.032f);

	mLightingShader->SetUniform("pointLights[1].position",  pointLightPositions[1]);
	mLightingShader->SetUniform("pointLights[1].ambient",   glm::vec3(0.05f, 0.05f, 0.05f));
	mLightingShader->SetUniform("pointLights[1].diffuse",   glm::vec3(0.8f, 0.8f, 0.8f));
	mLightingShader->SetUniform("pointLights[1].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
	mLightingShader->SetUniform("pointLights[1].constant",  1.0f);
	mLightingShader->SetUniform("pointLights[1].linear",    0.09f);
	mLightingShader->SetUniform("pointLights[1].quadratic", 0.032f);

	mLightingShader->SetUniform("pointLights[2].position",  pointLightPositions[2]);
	mLightingShader->SetUniform("pointLights[2].ambient",   glm::vec3(0.05f, 0.05f, 0.05f));
	mLightingShader->SetUniform("pointLights[2].diffuse",   glm::vec3(0.8f, 0.8f, 0.8f));
	mLightingShader->SetUniform("pointLights[2].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
	mLightingShader->SetUniform("pointLights[2].constant",  1.0f);
	mLightingShader->SetUniform("pointLights[2].linear",    0.09f);
	mLightingShader->SetUniform("pointLights[2].quadratic", 0.032f);

	mLightingShader->SetUniform("pointLights[3].position",  pointLightPositions[3]);
	mLightingShader->SetUniform("pointLights[3].ambient",   glm::vec3(0.05f, 0.05f, 0.05f));
	mLightingShader->SetUniform("pointLights[3].diffuse",   glm::vec3(0.8f, 0.8f, 0.8f));
	mLightingShader->SetUniform("pointLights[3].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
	mLightingShader->SetUniform("pointLights[3].constant",  1.0f);
	mLightingShader->SetUniform("pointLights[3].linear",    0.09f);
	mLightingShader->SetUniform("pointLights[3].quadratic", 0.032f);

	glm::mat4 view;
	view = mCamera->GetView();
	glm::mat4 proj = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	mLightingShader->SetUniform("view", view);
	mLightingShader->SetUniform("projection", proj);

	mDiffuse->Bind(0);
	mSpecular->Bind(1);
	glm::mat4 model;
	glBindVertexArray(mVao);
	for (GLuint i = 0; i < 10; i++)
	{
		model = glm::mat4();
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		mLightingShader->SetUniform("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
	mSpecular->Unbind();
	mDiffuse->Unbind();

	mLampShader->Bind();
	mLampShader->SetUniform("view", view);
	mLampShader->SetUniform("projection", proj);

	model = glm::mat4();
	glBindVertexArray(mLightVao);
	for (GLuint i = 0; i < 4; i++)
	{
		model = glm::mat4();
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		mLampShader->SetUniform("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

void Application::Cleanup()
{
	delete mDiffuse;
	//delete mShader;
	delete mCamera;
}
