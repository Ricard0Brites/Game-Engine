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

#include "SDL_timer.h"
#include "Systems/Collision/CollisionSystem.h"

// FWD declarations
class Actor;
class SpriteComponent;

using namespace std;

class GameEngine
{
	friend CollisionSystem;
public:
	void init(string windowTitle, int windowWidth, int windowHeight);
	void start();
	
	GameEngine();
	~GameEngine();

private:
	class SDLWrapper* sdl;
	Window* _Window;
	Actor* _PlayerReference = nullptr;

	InputSystem _InputSystem;
	CollisionSystem _CollisionSystem;
	EventSystem _EventSystem;
	list<Actor*> _Actors;

	#pragma region DisplayNames
	map<string, unsigned int> DisplayNames = {};
	#pragma endregion

	#pragma region Time Management

protected:
	double DeltaTime = 0;

#pragma endregion
public:
// Creates an Actor of type T and returns a reference to said object
	template <typename T> T* CreateActor(T* Owner);

	void RemoveActor(Actor* ActorToRemove);

	SDL_Window* GetWindow() { return _Window->GetWindow(); }
	struct SDL_Renderer* GetRenderer() { return _Window->GetRenderer(); }

	Actor* GetPlayer() { return _PlayerReference; }
	void SetPlayerReference(Actor* NewReference) { if(!_PlayerReference) _PlayerReference = NewReference; }

	float GetDeltaSeconds() { return (float)DeltaTime; }

};

template <typename T> T* GameEngine::CreateActor(T* Owner)
{
	std::string DisplayName = typeid(T).name();
	string cachedName = "";
	string::size_type i = DisplayName.find("class");
	if (i != string::npos)
		DisplayName.erase(i, 5);
	for(auto letter : DisplayName)
	{
		if(letter != ' ')
			cachedName += letter;
	}
	DisplayName = cachedName;

	if(DisplayNames.find(cachedName) != DisplayNames.end())
	{
		map<string, unsigned int>::iterator IT;
		IT = DisplayNames.find(cachedName);
		unsigned int index = IT->second;
		DisplayName.append("_");
		DisplayName.append(to_string(index));
		DisplayNames[cachedName] = index + 1;
	}
	else
	{
		DisplayNames.insert({cachedName, 1});
		DisplayName += "_0";
	}

	T* NewActor = new T(Owner);
	Actor* actor = dynamic_cast<Actor*>(NewActor);
	actor->ActorDisplayName = DisplayName;
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
	
	static EventSystem* GetEventSystem() { return _EventSystem; }
	static void SetEventSystem(EventSystem* EventSystemRef) { _EventSystem = EventSystemRef; }

	static SDL_Surface* LoadSurface(string filePath, SDL_Renderer* renderTarget);

	static Vector NormalizeVector(Vector VectorToNormalize);
	static float GetVectorNorm(const Vector* V);

	//to create child components of the sprite renderer
	static SDL_Texture* CreateTextureFromSurface(string TexturePath);
	static void QueryTexture(SDL_Texture* TextureToQuery, int &OutTextureWidth, int &OutTextureHeight);
	static void RenderTexture(SDL_Texture* TextureToRender, SDL_Rect* TexturePortion, SDL_Rect* DisplayQuad);

	//Delay
	static void Delay(float Sec) { SDL_Delay(Uint32(Sec * 1000)); }

	//screen data
	static void SetScreenDimentions(int Width, int Height) { _ScreenWidth = Width; _ScreenHeight = Height; }
	static int GetScreenWidth() { return _ScreenWidth; }
	static int GetScreenHeight() { return _ScreenHeight; }
private:
	static GameEngine* _GameEngineRef;
	static EventSystem* _EventSystem;
	static int _ScreenWidth, _ScreenHeight;
};