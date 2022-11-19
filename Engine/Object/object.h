#pragma once
#include "../../include/SDL2/SDL_events.h"

class Object
{
	
public:
	virtual void BeginPlay() = 0;
	virtual void Tick(float DeltaSeconds) = 0;
	virtual void OnKeyPressed(SDL_KeyCode KeyCode) = 0;
};
