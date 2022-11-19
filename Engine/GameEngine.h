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
class SpriteComponent;

class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();
	
	GameEngine();
	~GameEngine();

private:
	class SDLWrapper* sdl;
	 Window* _Window;


#pragma region Time Management

protected:
	double DeltaTime = 0;

#pragma endregion
	InputSystem _InputSystem;
	EventSystem _EventSystem;
	std::list<Actor*> _Actors;
public:
// Creates an Actor of type T and returns a reference to said object
	template <class T>
	T* CreateActor();

	SDL_Window* GetWindow() { return _Window->GetWindow(); }
	SDL_Renderer* GetRenderer() { return _Window->GetRenderer(); }

};

template <class T>
T* GameEngine::CreateActor()
{
	T* NewActor = new T;
	Actor* actor = dynamic_cast<Actor*>(NewActor);
	if (!actor) return nullptr; //Any object has to be a child of the Actor class
	_Actors.insert(_Actors.end(), actor);
	return NewActor;
}

class GameplayStatics
{
public:
	GameplayStatics();
	~GameplayStatics();

	// Game Engine Ref
	static GameEngine* GetGameEngine() { return _GameEngineRef; }
	static void SetGameEngineRef(GameEngine* NewReference) { _GameEngineRef = NewReference; }


private:
	static GameEngine* _GameEngineRef;
};