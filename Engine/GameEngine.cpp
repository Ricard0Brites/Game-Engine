#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include <iostream>

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight);
}

void GameEngine::start()
{
	bool isRunning = true;
	SDL_Event ev;
	
	//------- Game Loop -------------------------------------------------------------------------------
	while (isRunning)
	{
		_FrameStart = clock(); // Delta Time - frame Start

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}
		window->updateSurface();


		_FrameEnd = clock(); // DeltaTime Frame end
		DeltaTime = double(_FrameEnd - _FrameStart) / double(CLOCKS_PER_SEC); // Calculates the DeltaTime
		
		_TimeOfExecution = clock(); // Updates time of execution
	}
	//-------------------------------------------------------------------------------------------------
}

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
}
	