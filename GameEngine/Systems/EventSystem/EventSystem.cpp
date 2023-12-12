#include "EventSystem.h"
#include "..\..\GameEngine.h"
#include "..\Game\Player.h"

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
	if (!GameplayStatics::GetGameEngine()->GetPlayer())
	{
		LOG("Player Reference is null. When creating the player please call GameEngine->SetPlayerReference( YOURPLAYERREFERENCE );", 3);
		EXECUTIONLOG;
		return;
	}
	if(GameEngine* engine = GameplayStatics::GetGameEngine())
	{
		if(Actor* playerActor = engine->GetPlayer())
		{
			if(Player* player = static_cast<Player*>(playerActor))
				player->OnKeyPressed(KeyCode);
		}
	}
}

void EventSystem::TriggerOnInputRelease(InputKeyCodes KeyCode)
{
	if (!GameplayStatics::GetGameEngine()->GetPlayer())
	{
		LOG("Player Reference is null. When creating the player please call GameEngine->SetPlayerReference( YOURPLAYERREFERENCE );", 3);
		EXECUTIONLOG;
		return;
	}
	if(GameEngine* engine = GameplayStatics::GetGameEngine())
	{
		if(Actor* playerActor = engine->GetPlayer())
		{
			if(Player* player = static_cast<Player*>(playerActor))
				player->OnKeyReleased(KeyCode);
		}
	}
}

void EventSystem::TriggerOnInputAxis(InputKeyCodes KeyCode, Vector Data)
{
	if (!GameplayStatics::GetGameEngine()->GetPlayer())
	{
		LOG("Player Reference is null. When creating the player please call GameEngine->SetPlayerReference( YOURPLAYERREFERENCE );", 3);
		EXECUTIONLOG;
		return;
	}
	if(GameEngine* engine = GameplayStatics::GetGameEngine())
	{
		if(Actor* playerActor = engine->GetPlayer())
		{
			if(Player* player = static_cast<Player*>(playerActor))
				player->OnInputAxis(KeyCode, Data);
		}
	}
}
