#include "Window.h"
#include "glew.h"
#include "InitError.h"
#include "SDL_opengl.h"



Window::Window(std::string title, int windowWidth, int windowHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (_Window == nullptr)	throw InitError();
	glViewport(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight);
	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);
	if(!_Renderer) throw InitError();
	SDL_GLContext context = SDL_GL_CreateContext(_Window);
	glewInit();
}

struct SDL_Surface* Window::getSurface()
{
	return SDL_GetWindowSurface(_Window);
}

void Window::updateSurface()
{
	SDL_UpdateWindowSurface(_Window);
}

Window::~Window()
{
	SDL_DestroyWindow(_Window);
}
