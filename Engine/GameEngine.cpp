#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"

GameEngine::~GameEngine()
{
	delete _Window;
	delete sdl;
}

GameEngine::GameEngine()
{
	GameplayStatics::SetGameEngineRef(this);
}

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	_Window = new Window(windowTitle, windowWidth, windowHeight);
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
		_Window->updateSurface();
		

		if(GameplayStatics::GetEventSystem()) 
		{
		LOG("tjdncklsndflkjsdn", 3);
		}

#pragma region Event System

		SDL_RenderClear(GameplayStatics::GetGameEngine()->GetRenderer()); // clear screen
			for (auto const &actor : _Actors)
			{
				//triggers all beginplays evey tick in case any new object is added.
				_EventSystem.TriggerBeginPlay(actor);
			}
			for (auto const& actor : _Actors)
			{
				_EventSystem.TriggerTick(actor, (float)DeltaTime);// render present
			}
		SDL_RenderPresent(GameplayStatics::GetGameEngine()->GetRenderer()); // render
#pragma endregion
	}
	//-------------------------------------------------------------------------------------------------
}

// GameplayStatics -------------------------------

GameEngine* GameplayStatics::_GameEngineRef; // static variable definition
EventSystem* GameplayStatics::_EventSystem;	// static variable definition

GameplayStatics::GameplayStatics()
{
}

GameplayStatics::~GameplayStatics()
{
}

SDL_Surface* GameplayStatics::LoadSurface(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (!surface) 
	{
		LOG("Null Surface", 3);
	}
	return surface;
}

Vector GameplayStatics::NormalizeVector(Vector VectorToNormalize)
{
	
	float VectorNorm = (float)sqrt((VectorToNormalize.X * VectorToNormalize.X) + (VectorToNormalize.Y * VectorToNormalize.Y) + (VectorToNormalize.Z * VectorToNormalize.Z));

	Vector NewVec = Vector::CreateVector(VectorToNormalize.X / VectorNorm, VectorToNormalize.Y / VectorNorm, VectorToNormalize.Z / VectorNorm);

	return NewVec;

}
