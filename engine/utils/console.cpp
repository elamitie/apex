#include "console.h"

bool Console::DebugEnabled = false;

Console::Console()
{

}

Console::~Console()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

void Console::Init(Window* window)
{
	ImGui_ImplGlfwGL3_Init(window->m_window, false);
}

void Console::Begin()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

// -- Where the actual rendering of the console window takes place, calls to ImGUI
void Console::Render()
{
	ImGui::Begin("Debug");
	ImGui::Text("Framerate: %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
	for (auto &str : mUserData)
		ImGui::Text(str.c_str());
	ImGui::End();
}

// -- The name is end but the internal call is to Render. Think of it more like a Flush().
void Console::End()
{
	ImGui::Render();

	// For now, we'll just clear this every frame. Maybe in the future I want time based logging.
	mUserData.clear();
}

void Console::Log(const std::string& data)
{
	mUserData.push_back(data);
}