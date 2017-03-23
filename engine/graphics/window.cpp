#include "window.h"
#include "../utils/console.h"
#include "../input/keyboard.h"
#include <iostream>

#include "utils/logger.h"

Window::Window(int width, int height, const char* title) {
    // Initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);

    // Temporary, in the future probably support different resolutions?
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = glfwCreateWindow(width, height, title, nullptr,
                                nullptr);
    if (m_window == nullptr) {
        // TODO: Error handling someday
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    m_width = width;
    m_height = height;

    glfwMakeContextCurrent(m_window);
    if (glewInit() != GLEW_OK) {
        // TODO: Error handling someday
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    std::string glVersion = "OpenGL Version: " +
                            std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    Logger::Log(glVersion);

    glfwSetKeyCallback(m_window, key_callback);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::open() {
    return !glfwWindowShouldClose(m_window);
}

void Window::update() {
    glfwPollEvents();
    Keyboard::update();
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setColor(Color color) {
    glClearColor(color.r / 255.f, color.g / 255.f,
                 color.b / 255.f, color.a / 255.f);
}

static void key_callback(GLFWwindow* window, int key,
                         int scancode, int action, int mods) {
    //if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    //  Console::ToggleDebug();
    if (action == GLFW_PRESS)
        Keyboard::__hardwareKeyPress(key);
    if (action == GLFW_RELEASE)
        Keyboard::__hardwareKeyRelease(key);
}