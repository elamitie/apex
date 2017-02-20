#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });
	/*mShader = new Shader("../resources/shaders/basic_texture.vert", "../resources/shaders/basic_texture.frag");
	mShader->AddAttribute("position");
	mShader->AddAttribute("color");
	mShader->AddAttribute("texCoord");*/
	mLightingShader = new Shader("../resources/shaders/basic_lighting.vert", "../resources/shaders/basic_lighting.frag");
	mLightingShader->AddAttribute("position");
	mLightingShader->AddAttribute("normal");
	mLampShader = new Shader("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	mLampShader->AddAttribute("position");

	mTexture = new Texture2D();
	mTexture->Load("../resources/textures/bricks.jpg");

	SetClearColor({ 114, 144, 154 });

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

void Application::Update(float dt)
{
	if (Keyboard::KeyDown(GLFW_KEY_W))
		mCamera->HandleKeyboard(CamForward, dt);
	if (Keyboard::KeyDown(GLFW_KEY_S))
		mCamera->HandleKeyboard(CamBack, dt);
	if (Keyboard::KeyDown(GLFW_KEY_A))
		mCamera->HandleKeyboard(CamLeft, dt);
	if (Keyboard::KeyDown(GLFW_KEY_D))
		mCamera->HandleKeyboard(CamRight, dt);
}

void Application::Render(float dt)
{
	////mShader->Bind();
	////mTexture->Bind();

	////mShader->SetUniform("ourTexture", 0);
	//
	//glm::mat4 model;
	////model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	////model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//glm::mat4 view;
	//view = mCamera->GetView();
	//glm::mat4 projection;
	//projection = projection = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	///*mShader->SetUniform("model", model);
	//mShader->SetUniform("view", view);
	//mShader->SetUniform("projection", projection);*/

	///*glBindVertexArray(mVao);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);*/

	////mTexture->Unbind();
	////mShader->Unbind();

	mLightingShader->Bind();
}

void Application::Cleanup()
{
	delete mTexture;
	//delete mShader;
	delete mCamera;
}
