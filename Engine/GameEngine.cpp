#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"


void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight);
}

void GameEngine::start()
{
	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}
		window->updateSurface();
	}
}

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
}
