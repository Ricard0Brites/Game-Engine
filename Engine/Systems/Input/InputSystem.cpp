#include "InputSystem.h"
#include "..\..\Data\DataTypes.h"
#include "..\..\GameEngine.h"
#include <thread>
#include <iostream>

class thread;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

Vector* StickAxisVector = new Vector;
void InputSystem::ListenForInput(SDL_Event* key)
{
	if ((*key).type == SDL_KEYDOWN)
	{
		if (_KeyState.GetKeyState((*key).key.keysym.sym) != 1) // If the key is not pressed already
		{
			_KeyState.SetKeyState((*key).key.keysym.sym, true);
			GameplayStatics::GetEventSystem()->TriggerOnInputPress(_KeyState.GetKeyCode(key, false));
		}
	}

	if ((*key).type == SDL_KEYUP)
	{
		if (_KeyState.GetKeyState((*key).key.keysym.sym) == 1) //if the key is pressed already
		{
			_KeyState.SetKeyState((*key).key.keysym.sym, false);
			GameplayStatics::GetEventSystem()->TriggerOnInputRelease(_KeyState.GetKeyCode(key, false));
		}
	}

	if ((*key).type == SDL_JOYAXISMOTION)
	{
		bool canTriggerInput = false;

		if ((*key).jaxis.which == 0) //Controller id
		{
			if ((*key).jaxis.axis == 0) //Horizontal axis
			{
				if ((*key).jaxis.value < -_ControllerDeadzone || (*key).jaxis.value > _ControllerDeadzone)
				{
					*StickAxisVector = Vector::CreateVector((*key).jaxis.value / 32768.f, StickAxisVector->Y, StickAxisVector->Z);
					canTriggerInput = true;
				}
			}

			if ((*key).jaxis.axis == 1) //Vertical axis
			{
				if ((*key).jaxis.value < -_ControllerDeadzone || (*key).jaxis.value > _ControllerDeadzone)
				{
					*StickAxisVector = Vector::CreateVector(StickAxisVector->X, (*key).jaxis.value / 32768.f, StickAxisVector->Z);
					canTriggerInput = true;
				}
			}
		}
		if(canTriggerInput) GameplayStatics::GetEventSystem()->TriggerOnInputAxis(InputKeyCodes::GamepadStickLeft, *StickAxisVector);
	}

	if ((*key).type == SDL_JOYBUTTONDOWN)
	{
		if (_KeyState.GetKeyState((*key).jbutton.button + 1) != 1 ) // If the key is not pressed already
		{
			if ((*key).jbutton.which == 0)
			{
				_KeyState.SetKeyState((*key).jbutton.button + 1, true);
				
				GameplayStatics::GetEventSystem()->TriggerOnInputPress(_KeyState.GetKeyCode(key, true));
			}
		}
	}

	if ((*key).type == SDL_JOYBUTTONUP)
	{
		if (_KeyState.GetKeyState((*key).jbutton.button + 1) == 1) //if the key is pressed already
		{

			if ((*key).jbutton.which == 0)
			{
				_KeyState.SetKeyState((*key).jbutton.button + 1, false);

				GameplayStatics::GetEventSystem()->TriggerOnInputRelease(_KeyState.GetKeyCode(key, true));
			}
		}
	}

	if ((*key).type == SDL_JOYHATMOTION)
	{
		switch ((*key).jhat.value)
		{
			case 0:
				if (_KeyState.GetKeyState(lastKey) == 1)
				{
					_KeyState.SetKeyState(lastKey, false);
					GameplayStatics::GetEventSystem()->TriggerOnInputRelease(_KeyState.GetKeyCode(&lastKeyCopy, true, true));
				}
				break;
			default:
				if (_KeyState.GetKeyState((*key).jhat.value * 1000) != 1)
				{
					_KeyState.SetKeyState((*key).jhat.value * 1000, true);
					lastKey = (*key).jhat.value * 1000;\
					lastKeyCopy = *key;

					GameplayStatics::GetEventSystem()->TriggerOnInputPress(_KeyState.GetKeyCode(key, true, true));
				}
				break;
		}
	}	
}

// KeyPress -------------------------------------------------------

bool KeyPress::SetKeyState(int key, bool NewState)
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

int KeyPress::GetKeyState(int key)
{
	if (_keyState.find(key) == _keyState.end()) return -1;
	return _keyState[key];
}

InputKeyCodes KeyPress::GetKeyCode(SDL_Event* Key, bool IsControllerInput, bool IsJHat)
{
	if (IsControllerInput)
	{
		#pragma region Gamepad Input
		if (IsJHat)
		{
			switch ((*Key).jhat.value)
			{
			case 1:
				return GamepadArrowTop;
				break;

			case 2:
				return GamepadArrowRight;
				break;

			case 4:
				return GamepadArrowBottom;
				break;

			case 8:
				return GamepadArrowLeft;
				break;
			}
		}
		else
		{
			switch ((*Key).jbutton.button + 1)
			{
				case 1:
					return GamepadFaceBottom;
					break;
				case 2: 
					return GamepadFaceRight;
					break;
				case 3: 
					return GamepadFaceLeft;
					break;
				case 4: 
					return GamepadFaceTop;
					break;
				case 5:
					return GamepadLeftButton;
					break;
				case 6: 
					return GamepadRightButton;
					break;
				case 7: 
					return GamepadSpecialLeft;
					break;
				case 8: 
					return GamepadSpecialRight;
					break;
				case 9: 
					return GamepadLeftStickPress;
					break;
				case 10: 
					return GamepadRightStickPress;
					break;
			}	
		}
		
		#pragma endregion
	}
	else
	{
		#pragma region Keyboard Input
		switch ((*Key).key.keysym.sym)
		{
			case SDLK_a:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_A;
				return InputKeyCodes::K_a;
				break;

			case SDLK_b:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_B;
				return InputKeyCodes::K_b;
				break;

			case SDLK_c:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_C;
				return InputKeyCodes::K_c;
				break;

			case SDLK_d:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_D;
				return InputKeyCodes::K_d;
				break;

			case SDLK_e:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_E;
				return InputKeyCodes::K_e;
				break;

			case SDLK_f:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_F;
				return InputKeyCodes::K_f;
				break;

			case SDLK_g:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_G;
				return InputKeyCodes::K_g;
				break;

			case SDLK_h:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_H;
				return InputKeyCodes::K_h;
				break;

			case SDLK_i:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_I;
				return InputKeyCodes::K_i;
				break;

			case SDLK_j:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_J;
				return InputKeyCodes::K_j;
				break;

			case SDLK_k:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_K;
				return InputKeyCodes::K_k;
				break;

			case SDLK_l:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_L;
				return InputKeyCodes::K_l;
				break;

			case SDLK_m:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_M;
				return InputKeyCodes::K_m;
				break;

			case SDLK_n:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_N;
				return InputKeyCodes::K_n;
				break;

			case SDLK_o:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_O;
				return InputKeyCodes::K_o;
				break;

			case SDLK_p:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_P;
				return InputKeyCodes::K_p;
				break;

			case SDLK_q:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Q;
				return InputKeyCodes::K_q;
				break;

			case SDLK_r:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_R;
				return InputKeyCodes::K_r;
				break;

			case SDLK_s:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_S;
				return InputKeyCodes::K_s;
				break;

			case SDLK_t:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_T;
				return InputKeyCodes::K_t;
				break;

			case SDLK_u:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_U;
				return InputKeyCodes::K_u;
				break;

			case SDLK_v:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_V;
				return InputKeyCodes::K_v;
				break;

			case SDLK_w:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_W;
				return InputKeyCodes::K_w;
				break;

			case SDLK_x:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_X;
				return InputKeyCodes::K_x;
				break;

			case SDLK_y:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Y;
				return InputKeyCodes::K_y;
				break;

			case SDLK_z:
				if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Z;
				return InputKeyCodes::K_z;
				break;
			case SDLK_SPACE:
				return InputKeyCodes::K_Space;
				break;
			case SDLK_UP:
				return InputKeyCodes::K_Up;
				break;
			case SDLK_LEFT:
				return InputKeyCodes::K_Left;
				break;
			case SDLK_DOWN:
				return InputKeyCodes::K_Down;
				break;
			case SDLK_RIGHT:
				return InputKeyCodes::K_Right;
				break;
			}
		#pragma endregion
	}
	return InputKeyCodes::Null; 
}

InputKeyCodes KeyPress::GetKeyCode(SDL_Event* Key, bool IsControllerInput)
{
	if (IsControllerInput)
	{
		switch ((*Key).jbutton.button + 1)
		{
		case 1:
			return GamepadFaceBottom;
			break;
		case 2:
			return GamepadFaceRight;
			break;
		case 3:
			return GamepadFaceLeft;
			break;
		case 4:
			return GamepadFaceTop;
			break;
		case 5:
			return GamepadLeftButton;
			break;
		case 6:
			return GamepadRightButton;
			break;
		case 7:
			return GamepadSpecialLeft;
			break;
		case 8:
			return GamepadSpecialRight;
			break;
		case 9:
			return GamepadLeftStickPress;
			break;
		case 10:
			return GamepadRightStickPress;
			break;
		}
	}
	else
	{
		#pragma region Keyboard Input
		switch ((*Key).key.keysym.sym)
		{
		case SDLK_a:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_A;
			return InputKeyCodes::K_a;
			break;

		case SDLK_b:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_B;
			return InputKeyCodes::K_b;
			break;

		case SDLK_c:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_C;
			return InputKeyCodes::K_c;
			break;

		case SDLK_d:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_D;
			return InputKeyCodes::K_d;
			break;

		case SDLK_e:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_E;
			return InputKeyCodes::K_e;
			break;

		case SDLK_f:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_F;
			return InputKeyCodes::K_f;
			break;

		case SDLK_g:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_G;
			return InputKeyCodes::K_g;
			break;

		case SDLK_h:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_H;
			return InputKeyCodes::K_h;
			break;

		case SDLK_i:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_I;
			return InputKeyCodes::K_i;
			break;

		case SDLK_j:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_J;
			return InputKeyCodes::K_j;
			break;

		case SDLK_k:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_K;
			return InputKeyCodes::K_k;
			break;

		case SDLK_l:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_L;
			return InputKeyCodes::K_l;
			break;

		case SDLK_m:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_M;
			return InputKeyCodes::K_m;
			break;

		case SDLK_n:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_N;
			return InputKeyCodes::K_n;
			break;

		case SDLK_o:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_O;
			return InputKeyCodes::K_o;
			break;

		case SDLK_p:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_P;
			return InputKeyCodes::K_p;
			break;

		case SDLK_q:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Q;
			return InputKeyCodes::K_q;
			break;

		case SDLK_r:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_R;
			return InputKeyCodes::K_r;
			break;

		case SDLK_s:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_S;
			return InputKeyCodes::K_s;
			break;

		case SDLK_t:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_T;
			return InputKeyCodes::K_t;
			break;

		case SDLK_u:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_U;
			return InputKeyCodes::K_u;
			break;

		case SDLK_v:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_V;
			return InputKeyCodes::K_v;
			break;

		case SDLK_w:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_W;
			return InputKeyCodes::K_w;
			break;

		case SDLK_x:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_X;
			return InputKeyCodes::K_x;
			break;

		case SDLK_y:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Y;
			return InputKeyCodes::K_y;
			break;

		case SDLK_z:
			if (GetKeyState(SDLK_LSHIFT) == 1 || GetKeyState(SDLK_RSHIFT) == 1) return K_Z;
			return InputKeyCodes::K_z;
			break;
		case SDLK_SPACE:
			return InputKeyCodes::K_Space;
			break;
		case SDLK_UP:
			return InputKeyCodes::K_Up;
			break;
		case SDLK_LEFT:
			return InputKeyCodes::K_Left;
			break;
		case SDLK_DOWN:
			return InputKeyCodes::K_Down;
			break;
		case SDLK_RIGHT:
			return InputKeyCodes::K_Right;
			break;
		}
#pragma endregion
	}
	return InputKeyCodes::Null;
}
