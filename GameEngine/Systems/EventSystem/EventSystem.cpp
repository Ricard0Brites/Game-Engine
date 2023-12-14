#include "EventSystem.h"
#include "GameEngine.h"

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

void EventSystem::TriggerTick(Actor* actor, float DeltaSeconds)
{
	if(actor->IsPendingKill)
		return;
	actor->Tick(DeltaSeconds);
}

void EventSystem::TriggerBeginPlay(Actor* actor)
{
	if(actor->HasInit) return;
	actor->BeginPlay(); //only triggers if the actor hasn't been initialized yet
	actor->HasInit = true;
}

void EventSystem::TriggerOnInputPress(InputKeyCodes KeyCode)
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef,);
	Actor* PlayerReference = EngineRef->GetPlayer();
	Validate(PlayerReference,);
	if(PlayerReference->IsPendingKill)
		return;
	PlayerReference->OnKeyPressed(KeyCode);
}

void EventSystem::TriggerOnInputRelease(InputKeyCodes KeyCode)
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );
	Actor* PlayerReference = EngineRef->GetPlayer();
	Validate(PlayerReference, );
	if(PlayerReference->IsPendingKill)
		return;
	PlayerReference->OnKeyReleased(KeyCode);
}

void EventSystem::TriggerOnInputAxis(InputKeyCodes KeyCode, Vector Data)
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );
	Actor* PlayerReference = EngineRef->GetPlayer();
	Validate(PlayerReference, );
	if(PlayerReference->IsPendingKill)
		return;
	PlayerReference->OnInputAxis(KeyCode, Data);
}
