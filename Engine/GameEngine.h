#pragma once
#include <string>
#include <time.h>

class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	~GameEngine();

private:
	class SDLWrapper* sdl;
	class Window* window;

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

};

