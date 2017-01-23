#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "utils/color.h"

bool DEBUG_ENABLED = false;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
		DEBUG_ENABLED = !DEBUG_ENABLED;
}

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return -1;

	glfwSetKeyCallback(window, key_callback);

	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, false);

	bool show_test_window = true;
	bool show_another_window = false;
	Color color{ 114, 144, 154 };
	ImVec4 clear_color = color.CreateImColor();
	
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		if (DEBUG_ENABLED)
		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}