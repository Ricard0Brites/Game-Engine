#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Logger/Logger.h"

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
		// Delta Time - frame Start
		_FrameStart = clock(); 

		// Stops execution
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)isRunning = false;

	
		//Call listem for input function here (&ev)
		_InputSystem.ListenForInput(&ev);

		window->updateSurface();
		
		// DeltaTime Frame end
		_FrameEnd = clock(); 
		DeltaTime = double(_FrameEnd - _FrameStart) / double(CLOCKS_PER_SEC);
		
		_TimeOfExecution = clock(); // Updates time of execution
	}
	//-------------------------------------------------------------------------------------------------
}

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
	delete &_InputSystem;
}
