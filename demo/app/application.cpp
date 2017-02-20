#include "application.h"
#include "input/keyboard.h"

void Application::Init()
{
	mCamera = new Camera({ 0.0f, 0.0f, 3.0f });
	mShader = new Shader("../resources/shaders/basic_texture.vert", "../resources/shaders/basic_texture.frag");
	mShader->AddAttribute("position");
	mShader->AddAttribute("color");
	mShader->AddAttribute("texCoord");

	mTexture = new Texture2D();
	mTexture->Load("../resources/textures/bricks.jpg");

	mSphere = new Sphere(32, 32);
	mSphere->SetTextures({ mTexture });

	SetClearColor({ 114, 144, 154 });

	//glGenVertexArrays(1, &mVao);
	//glGenBuffers(1, &mVbo);
	//glGenBuffers(1, &mIbo);

	//glBindVertexArray(mVao);

	//glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// Position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//// TexCoord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//glBindVertexArray(0); // Unbind VAO
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
	mShader->Bind();
	//mTexture->Bind();

	//mShader->SetUniform("ourTexture", 0);
	
	glm::mat4 model;
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view;
	view = mCamera->GetView();
	glm::mat4 projection;
	projection = projection = glm::perspective(mCamera->Properties.Zoom, (GLfloat)GetWidth() / (GLfloat)GetHeight(), 0.1f, 100.0f);

	mShader->SetUniform("model", model);
	mShader->SetUniform("view", view);
	mShader->SetUniform("projection", projection);

	mSphere->Draw(mShader);

	/*glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	//mTexture->Unbind();
	mShader->Unbind();
}

void Application::Cleanup()
{
	delete mTexture;
	delete mShader;
	delete mCamera;
}
