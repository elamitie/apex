#include <stdio.h>
#include <iostream>

#include "utils/console.h"
#include "utils/color.h"


int main(int, char**)
{
	Console* console = new Console();
	Window* window = new Window(800, 600, "OpenGL Renderer");

	console->Init(window);
	window->SetClearColor({ 114, 144, 154 });
	
	// Main loop
	while (window->Open())
	{
		window->Clear();
		window->Update();

		console->Begin();
		if (Console::DebugEnabled)
			console->Render();

		console->End();
		
		window->SwapBuffers();
	}

	// Cleanup
	delete window;
	delete console;

	return 0;
}