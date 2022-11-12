#pragma once
#include "..\..\Object\object.h"
#include "../../Object/Actor.h"

class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	void TriggerTick(Actor* actor, float DeltaSeconds);
	void TriggerBeginPlay(Actor* actor);

private:

};