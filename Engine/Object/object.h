#pragma once
#include "../../include/SDL2/SDL_events.h"
#include "../Data/DataTypes.h"

enum InputKeyCodes;
class Vector;

class Object
{
	
public:
	virtual void BeginPlay() = 0;
	virtual void Tick(float DeltaSeconds) = 0;
	virtual void OnKeyPressed(InputKeyCodes KeyCode) = 0;
	virtual void OnKeyReleased(InputKeyCodes KeyCode) = 0;
	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) = 0;
};
