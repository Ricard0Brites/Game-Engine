#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Logger/Logger.h"

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
}

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
		
#pragma region Event System

		for (Actor* actor : _Actors)
		{
			_EventSystem.TriggerBeginPlay(actor);
		}
		for (Actor* actor : _Actors)
		{
			_EventSystem.TriggerTick(actor, DeltaTime);
		}
#pragma endregion
	}
	//-------------------------------------------------------------------------------------------------
}

template <typename T>
T* GameEngine::CreateActor()
{
	T NewActor = new T;
	Actor* actor = dynamic_cast<Actor*>(&NewActor);
	if(!actor) return nullptr; //Any object has to be a child of the Actor class
	_Actors.push_back(actor);
	return &NewActor;
}
