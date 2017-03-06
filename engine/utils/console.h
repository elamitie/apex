#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

#include "../graphics/window.h"
#include <string>
#include <vector>

// Going to be a wrapper for IMGUI; a simple console debug window.

class Console
{
public:
	static bool DebugEnabled;
public:
	Console();
	~Console();

	void Init(Window* window);
	void Begin();
	void Render();
	void End();

	void Log(const std::string& data);

	inline static void ToggleDebug() { DebugEnabled = !DebugEnabled; }

private:
	std::vector<std::string> mUserData;
};