#pragma once
#include <string>
class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);

	void start();

	~GameEngine();
private:
	class SDLWrapper* sdl;
	class Window* window;
};

