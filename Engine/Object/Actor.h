#pragma once
#include "object.h"

class Actor : Object
{
public:
	Actor();
	~Actor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(SDL_KeyCode KeyCode) override;

	bool HasInit = false;
};