#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"

GameEngine::~GameEngine()
{
	delete _Window;
	delete sdl;
	for(auto Actor : _Actors)
	{
		delete Actor;
	}
}

void GameEngine::RemoveActor(Actor* ActorToRemove)
{
	ActorToRemove->IsPendingKill = true;
	LOG("Adding Actor To Pending Kill List", 0);
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
	_Renderer.Init();
}

void GameEngine::start()
{
	SDL_Event ev;

	//Delta Time
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;

	//------- Game Loop -------------------------------------------------------------------------------
	while (IsRunning)
	{
		if(_PlayerReference->IsPendingKill)
			QuitGame();
		#pragma region Delta Time
		last = now;
		now = SDL_GetPerformanceCounter();
		DeltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
		#pragma endregion

		SDL_PollEvent(&ev);
		// Stops execution
		if (ev.type == SDL_QUIT)
		{
			IsRunning = false;
			break;
		}

		//listen for input
		_InputSystem.ListenForInput(&ev);

		//Check Collisions
		_CollisionSystem.CheckCollision();

		#pragma region Event System
		SDL_RenderClear(GameplayStatics::GetGameEngine()->GetRenderer()); // clear screen
			for (auto const &actor : _Actors)
			{
				//triggers all beginplays evey tick in case any new object is added.
				if(actor)_EventSystem.TriggerBeginPlay(actor);

			}
			for (auto const& actor : _Actors)
			{
				if(actor)_EventSystem.TriggerTick(actor, (float)DeltaTime);				
			}
		#pragma endregion

		// Render
		// TODO - call renderer here
		_Renderer.Render();
		_Window->updateSurface();
		SDL_RenderPresent(GameplayStatics::GetGameEngine()->GetRenderer());
		SDL_GL_SwapWindow(_Window->GetWindow());

		#pragma region Clean Pending Kill Actors
		std::list<Actor*> Cache = _Actors;
		for (Actor* actor : _Actors)
		{
			if(actor->IsPendingKill)
			{
				Cache.remove(actor);

				#if _DEBUG
				printf("Deleting %s \n", actor->ActorDisplayName.c_str());
				#endif

				if(actor == _PlayerReference)
				{
					delete actor;
					QuitGame();
				}
				else
					delete actor;
			}
		}
		_Actors = Cache;
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

float GameplayStatics::GetVectorNorm(const Vector* V)
{
	return sqrt((V->X * V->X) + (V->Y * V->Y) + (V->Z * V->Z));
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