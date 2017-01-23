#include "window.h"
#include "../utils/console.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
{
	// Initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Temporary, in the future probably support different resolutions?
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		// TODO: Error handling someday
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	m_width = width;
	m_height = height;

	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
	{
		// TODO: Error handling someday
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	glfwSetKeyCallback(m_window, key_callback);

	// Rather than use the stored window width and height, using
	// local variables to set the viewport size will let it work
	// on high res displays like retina
	int _width, _height;
	glfwGetFramebufferSize(m_window, &_width, &_height);
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::Open()
{
	return !glfwWindowShouldClose(m_window);
}

void Window::Update()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::SetClearColor(Color color)
{
	glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	m_color = color;	
}

void Window::Clear()
{
	glClearColor(m_color.r / 255.f, m_color.g / 255.f, m_color.b / 255.f, m_color.a / 255.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
		Console::ToggleDebug();
}