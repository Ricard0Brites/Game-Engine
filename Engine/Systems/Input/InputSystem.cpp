#include "../../Logger/Logger.h"
#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{

}

void InputSystem::ListenForInput(SDL_Event* key)
{
	if ((*key).type == SDL_KEYDOWN)
	{
		if (_KeyState.GetKeyState((SDL_KeyCode)(*key).key.keysym.sym) == 0 || _KeyState.GetKeyState((SDL_KeyCode)(*key).key.keysym.sym) == -1) // If the key is not pressed already
		{
			switch ((*key).key.keysym.sym)
			{
				case SDLK_a:
				{
					LOG("A is Pressed - Move Left", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, true);
					break;
				}
				case SDLK_d:
				{
					LOG("D is Pressed - Move Right", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, true);
					break;
				}
				case SDLK_w:
				{
					LOG("W is Pressed - Move Up", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, true);
					break;
				}
				case SDLK_s:
				{
					LOG("S is Pressed - Move Down", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, true);
					break;
				}
				case SDLK_SPACE:
				{
					LOG("SPACEBAR is Pressed - Shoot", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, true);
					break;
				}
				default:
					break;
			}
		}
	}

	if ((*key).type == SDL_KEYUP)
	{
		if (_KeyState.GetKeyState((SDL_KeyCode)(*key).key.keysym.sym) == 1) //if the key is pressed already
		{

		
			switch ((*key).key.keysym.sym)
			{
				case SDLK_a:
				{
					LOG("A is Released - Move Left", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, false);
					break;
				}
				case SDLK_d:
				{
					LOG("D is Released - Move Right", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, false);
					break;
				}
				case SDLK_w:
				{
					LOG("W is Released - Move Up", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, false);
					break;
				}
				case SDLK_s:
				{
					LOG("S is Released - Move Down", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, false);
					break;
				}
				case SDLK_SPACE:
				{
					LOG("SPACEBAR is Released - Shoot", 0);
					_KeyState.SetKeyState((SDL_KeyCode)(*key).key.keysym.sym, false);
					break;
				}
				default:
					break;
			}
		}
	}
}

// KeyPress -------------------------------------------------------

bool KeyPress::SetKeyState(SDL_KeyCode key, bool NewState)
{
	if (!key && NewState == NULL) return false;
	
	if (_keyState.find(key) == _keyState.end()) 
	{
		//if key is doesn't exist in the map, add it
		_keyState.insert({key, NewState});
	}
	else
	{
		//if the key exists, change its value
		_keyState[key] = NewState;
	}
	return true;
}

int KeyPress::GetKeyState(SDL_KeyCode key)
{
	if (_keyState.find(key) == _keyState.end()) return -1;
	return _keyState[key];
}
