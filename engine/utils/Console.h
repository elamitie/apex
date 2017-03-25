#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

#include "../graphics/Window.h"
#include <string>
#include <vector>

// Going to be a wrapper for IMGUI; a simple console debug window.

class Console {
public:
    static bool DebugEnabled;
public:
    Console();
    ~Console();

    void init(Window* window);
    void begin();
    void render();
    void end();

    void log(const std::string& data);

    inline static void toggleDebug() { DebugEnabled = !DebugEnabled; }

private:
    std::vector<std::string> mUserData;
};