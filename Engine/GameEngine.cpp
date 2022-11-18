#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
}

GameEngine::GameEngine()
{
	GameplayStatics::GameEngineRef = this;
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

	//Delta Time
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;

	//------- Game Loop -------------------------------------------------------------------------------
	while (isRunning)
	{
#pragma region Delta Time
		last = now;
		now = SDL_GetPerformanceCounter();
		DeltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
#pragma endregion

		// Stops execution
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT) isRunning = false;

	
		//listen for input
		_InputSystem.ListenForInput(&ev);

		// Render
		window->updateSurface();
		
#pragma region Event System

		for (Actor* actor : _Actors)
		{
			//triggers all beginplays evey tick in case any new object is added.
			_EventSystem.TriggerBeginPlay(actor);
		}
		for (Actor* actor : _Actors)
		{
			_EventSystem.TriggerTick(actor, (float)DeltaTime);
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


// GameplayStatics -------------------------------

GameEngine* GameplayStatics::GameEngineRef; // static variable definition

GameplayStatics::GameplayStatics()
{
}

GameplayStatics::~GameplayStatics()
{
}