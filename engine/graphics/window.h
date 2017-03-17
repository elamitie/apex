#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/color.h"

class Window
{
    friend class Console;
    friend class Keyboard;
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool Open();

    void Update();
    void SwapBuffers();
    void Clear();
    void SetClearColor(Color color);

    inline int GetWidth() { return m_width; }
    inline int GetHeight() { return m_height; }
    inline float GetAspect() { return ((float)m_width / (float)m_height); }

private:
    GLFWwindow* m_window;
    int m_width, m_height;
    Color m_color;
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
