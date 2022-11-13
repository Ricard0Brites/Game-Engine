#pragma once
#include "../../include/SDL2/SDL_events.h"

class Object
{
public:
	Object();
	~Object();

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
	virtual void OnKeyPressed(SDL_KeyCode KeyCode);
};