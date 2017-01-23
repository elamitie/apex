#pragma once

// Going to be a wrapper for IMGUI; a simple console debug window.

class Console
{
public:
	Console();
	~Console();

private:
	// These could be public but I'm probably just going to friend them with
	// the engine / window.
	void Update();
	void Render();
};