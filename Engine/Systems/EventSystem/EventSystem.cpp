#include "EventSystem.h"
#include "../../Object/object.h"

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

void EventSystem::TriggerTick(Actor* actor, float DeltaSeconds)
{
	actor->Tick(DeltaSeconds);
}

void EventSystem::TriggerBeginPlay(Actor* actor)
{
	if(actor->HasInit) return;
	actor->BeginPlay(); //only triggers if the actor hasnt been initialized yet
	actor->HasInit = true;
}
