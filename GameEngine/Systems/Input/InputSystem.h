#pragma once

#include "SDL_events.h"
#include "Logger/Logger.h"
#include <map>
#include "Data/DataTypes.h"


struct KeyPress
{
private:
	std::map<int, bool> _keyState = {};

public:
	// Sets the state for the provided key code. If the key doesn't yet exist it will add it
	// Returns true if the operation was successful
	bool SetKeyState(int key, bool NewState);
	//Gets the state of the provided key
	// -1 = key not found
	// 0 = false
	// 1 = true
	int GetKeyState(int key);
	InputKeyCodes GetKeyCode(SDL_Event* Key, bool IsControllerInput, bool IsJHat);
	InputKeyCodes GetKeyCode(SDL_Event* Key, bool IsControllerInput);
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	// Listens for keyboard input

		// TODO: Add Controller Input Listener
	void ListenForInput(SDL_Event* key);
	void SetGamepadDeadzone(int NewDeadZone) { _ControllerDeadzone = NewDeadZone; }
private:
	unsigned int lastKey;
	SDL_Event lastKeyCopy;
	KeyPress _KeyState;
	int _ControllerDeadzone = 1500;

};

