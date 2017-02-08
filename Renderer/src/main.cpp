#include <stdio.h>
#include <iostream>

#include "utils/math.h"

#include "utils/console.h"
#include "utils/color.h"
#include "graphics/assets/shader.h"
#include "graphics/assets/texture.h"


int main(int, char**)
{
	Console* console = new Console();
	Window* window = new Window(800, 600, "OpenGL Renderer");
	// TODO: need some sort of GetAssetPath() function so I don't have to hardcode this
	Shader* shader = new Shader("resources/shaders/basic_texture.vert", "resources/shaders/basic_texture.frag");
	shader->AddAttribute("position");
	shader->AddAttribute("color");
	shader->AddAttribute("texCoord");

	Texture2D* texture = new Texture2D();
	texture->Load("resources/textures/bricks.jpg");

	console->Init(window);
	window->SetClearColor({ 114, 144, 154 });

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Quad positioning in the world
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = transform * vec;
	
	// Main loop
	while (window->Open())
	{
		window->Clear();
		window->Update();

		shader->Bind();
		texture->Bind();

		shader->SetUniform("ourTexture", 0);

		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection;
		projection = projection = glm::perspective(glm::radians(45.0f), (GLfloat)window->GetWidth() / (GLfloat)window->GetHeight(), 0.1f, 100.0f);

		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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