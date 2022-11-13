#pragma once
#include <string>
#include <time.h>
#include <iostream>
#include <list>

//systems
#include "Systems/Input/InputSystem.h"
#include "Systems/EventSystem/EventSystem.h"
#include "Logger/Logger.h"


class Actor;

class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	~GameEngine();

private:
	class SDLWrapper* sdl;
	class Window* window;
	bool _HasRun = false;

#pragma region Time Management
public:
	// Returns the time, in seconds, since the program has started running
	inline double GetTimeOfExecution() { return _TimeOfExecution; }

protected:
	double DeltaTime = 0;

private:
	/* Variables to calculate DeltaTime */
	clock_t _FrameStart, _FrameEnd;
	clock_t _TimeOfExecution;

#pragma endregion
	InputSystem _InputSystem;
	EventSystem _EventSystem;
	std::list<Actor*> _Actors;
public:
// Creates an Actor of type T and returns a reference to said object
	template <typename T>
	T* CreateActor();
};
