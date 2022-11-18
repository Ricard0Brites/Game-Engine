#pragma once
#include <string>
#include <time.h>
#include <iostream>
#include <list>

//systems
#include "Systems/Input/InputSystem.h"
#include "Systems/EventSystem/EventSystem.h"
#include "Logger/Logger.h"

#include "Window.h"

class Actor;

class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();
	
	GameEngine();
	~GameEngine();

private:
	class SDLWrapper* sdl;
	 Window* window;
	bool _HasRun = false;


#pragma region Time Management

protected:
	double DeltaTime = 0;

#pragma endregion
	InputSystem _InputSystem;
	EventSystem _EventSystem;
	std::list<Actor*> _Actors;
public:
// Creates an Actor of type T and returns a reference to said object
	template <typename T>
	T* CreateActor();

	SDL_Window* GetWindow() { return window->GetWindow(); }

};

class GameplayStatics
{
public:
	GameplayStatics();
	~GameplayStatics();

	static GameEngine* GameEngineRef;
};