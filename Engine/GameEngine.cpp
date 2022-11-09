#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Logger/Logger.h"
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
	
	system("Color 07");
	//------- Game Loop -------------------------------------------------------------------------------
	while (isRunning)
	{
		_FrameStart = clock(); // Delta Time - frame Start

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;

	
			ListenForInput(&ev);

			
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


void GameEngine::ListenForInput(SDL_Event* key)
{


	if ((*key).type == SDL_KEYDOWN)
	{
		//std::cout << "Key Pressed" << std::endl;

		if (SDLK_a == (*key).key.keysym.sym)
		{
			std::cout << "A is Pressed - Move Left" << std::endl;
		}
		else if (SDLK_d == (*key).key.keysym.sym)
		{
			std::cout << "D is Pressed - Move Right" << std::endl;
		}
		else if (SDLK_w == (*key).key.keysym.sym)
		{
			std::cout << "W is Pressed - Move Right" << std::endl;
		}
		else if (SDLK_s == (*key).key.keysym.sym)
		{
			std::cout << "S is Pressed - Move Right" << std::endl;
		}
		else if (SDLK_SPACE == (*key).key.keysym.sym)
		{
			std::cout << "D is Pressed - Move Right" << std::endl;
		}
	}

	if ((*key).type == SDL_KEYUP)
	{
		std::cout << "Key released" << std::endl;
	}




}
