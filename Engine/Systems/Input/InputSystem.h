#pragma once

#include "../../include/SDL2/SDL_events.h"
#include <map>


struct KeyPress
{
private:
	std::map<SDL_KeyCode, bool> _keyState = {};

public:
	// Sets the state for the provided key code. If the key doens't yet exist it will add it
	// Returns true if the operation was successful
	bool SetKeyState(SDL_KeyCode key, bool NewState);
	//Gets the state of the provided key
	// -1 = key not found
	// 0 = false
	// 1 = true
	int GetKeyState(SDL_KeyCode key);

};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	// Listens for keyboard input

		// TODO: Add Controller Input Listener
	void ListenForInput(SDL_Event* key);

private:
	KeyPress _KeyState;

};

