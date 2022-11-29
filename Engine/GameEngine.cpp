#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"

GameEngine::~GameEngine()
{
	delete _Window;
	delete sdl;
}

void GameEngine::RemoveActor(Actor* ActorToRemove)
{
	SDL_Delay((int)DeltaTime / 2); // waits roughly half a frame
	ActorToRemove->~Actor();
	_Actors.remove(ActorToRemove);
	LOG("Deleting Actor", 1);
}

GameEngine::GameEngine()
{
	GameplayStatics::SetGameEngineRef(this);
	GameplayStatics::SetEventSystem(&_EventSystem);
}

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	_Window = new Window(windowTitle, windowWidth, windowHeight);
	GameplayStatics::SetScreenDimentions(windowWidth, windowHeight);
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

#pragma region Event System

		SDL_RenderClear(GameplayStatics::GetGameEngine()->GetRenderer()); // clear screen
			for (auto const &actor : _Actors)
			{
				//triggers all beginplays evey tick in case any new object is added.
				_EventSystem.TriggerBeginPlay(actor);

			}
			for (auto const& actor : _Actors)
			{
				_EventSystem.TriggerTick(actor, (float)DeltaTime);				
			}
		SDL_RenderPresent(GameplayStatics::GetGameEngine()->GetRenderer()); // render
#pragma endregion
	}
	//-------------------------------------------------------------------------------------------------
}

// GameplayStatics -------------------------------

GameEngine* GameplayStatics::_GameEngineRef; // static variable definition

EventSystem* GameplayStatics::_EventSystem;	// static variable definition

int GameplayStatics::_ScreenWidth = 0;

int GameplayStatics::_ScreenHeight = 0;

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

SDL_Texture* GameplayStatics::CreateTextureFromSurface(std::string TexturePath)
{
	SDL_Surface* surface = GameplayStatics::LoadSurface(TexturePath, GameplayStatics::GetGameEngine()->GetRenderer());
	if (surface) SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));

	SDL_Texture* DisplaySprite = SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return DisplaySprite;
}

void GameplayStatics::QueryTexture(SDL_Texture* TextureToQuery, int& OutTextureWidth, int& OutTextureHeight)
{
	SDL_QueryTexture(TextureToQuery, NULL, NULL, &OutTextureWidth, &OutTextureHeight);
}

void GameplayStatics::RenderTexture(SDL_Texture* TextureToRender, SDL_Rect* TexturePortion, SDL_Rect* DisplayQuad)
{
	SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), TextureToRender, TexturePortion, DisplayQuad);
}
