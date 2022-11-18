#pragma once
#include <string>



class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	struct SDL_Surface* getSurface();
	struct SDL_Window* GetWindow() { return window; }

	void updateSurface();

	~Window();
private:
	struct SDL_Window* window;
};

