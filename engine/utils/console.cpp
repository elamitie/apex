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
	ImGui::Text("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

// -- The name is end but the internal call is to Render. Think of it more like a Flush().
void Console::End()
{
	ImGui::Render();
}