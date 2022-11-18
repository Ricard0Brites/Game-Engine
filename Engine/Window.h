#pragma once
#include <string>
class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	class SDL_Surface* getSurface();
	class SDL_Window* GetWindow() { return window; }

	void updateSurface();

	~Window();
private:
	class SDL_Window* window;
};

