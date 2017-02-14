#include <stdio.h>
#include <iostream>

#include "utils/math.h"

#include "utils/console.h"
#include "utils/color.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"
#include "graphics/view/camera.h"
#include "input/keyboard.h"


int main(int, char**)
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	Console* console = new Console();
	Window* window = new Window(800, 600, "OpenGL Renderer");
	Camera* camera = new Camera({ 0.0f, 0.0f, 3.0f });
	// TODO: need some sort of GetAssetPath() function so I don't have to hardcode this
	Shader* shader = new Shader("resources/shaders/basic_texture.vert", "resources/shaders/basic_texture.frag");
	shader->AddAttribute("position");
	shader->AddAttribute("color");
	shader->AddAttribute("texCoord");

	Texture2D* texture = new Texture2D();
	texture->Load("resources/textures/bricks.jpg");

	console->Init(window);
	window->SetClearColor({ 114, 144, 154 });
	
	Keyboard::Init();

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// World space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	
	// Main loop
	while (window->Open())
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window->Clear();
		window->Update();

		if (Keyboard::KeyDown(GLFW_KEY_W))
			camera->HandleKeyboard(CamForward, deltaTime);
		if (Keyboard::KeyDown(GLFW_KEY_S))
			camera->HandleKeyboard(CamBack, deltaTime);
		if (Keyboard::KeyDown(GLFW_KEY_A))
			camera->HandleKeyboard(CamLeft, deltaTime);
		if (Keyboard::KeyDown(GLFW_KEY_D))
			camera->HandleKeyboard(CamRight, deltaTime);

		shader->Bind();
		texture->Bind();

		shader->SetUniform("ourTexture", 0);

		glm::mat4 view;
		view = camera->GetView();
		glm::mat4 projection;
		projection = projection = glm::perspective(camera->Properties.Zoom, (GLfloat)window->GetWidth() / (GLfloat)window->GetHeight(), 0.1f, 100.0f);

		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			
			shader->SetUniform("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		texture->Unbind();
		shader->Unbind();
		
		window->SwapBuffers();
	}

	// Cleanup
	delete texture;
	delete shader;
	delete window;
	delete console;

	return 0;
}