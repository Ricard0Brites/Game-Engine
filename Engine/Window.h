#pragma once
#include <string>



class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	struct SDL_Surface* getSurface();
	struct SDL_Window* GetWindow() { return _Window; }
	struct SDL_Renderer* GetRenderer() { return _Renderer; }

	void updateSurface();

	~Window();
private:
	struct SDL_Window* _Window;
	struct SDL_Renderer* _Renderer = nullptr;
};

