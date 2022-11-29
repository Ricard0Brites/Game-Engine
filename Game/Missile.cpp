#include "Missile.h"
#include "GameEngine.h"
#include "GameRules.h"
#include "Manager\RocketManager.h"
#include "..\include\SDL2\SDL_timer.h"

#include <thread>

Missile::Missile(Actor* Parent) :Actor(Parent)
{
	RocketSpeed = GameRules::GetRocketMovementSpeed();
}

Missile::~Missile()
{
}

void Missile::BeginPlay()
{
	Actor::BeginPlay();
}

void Missile::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	if (!CanMove) return;
	GetTransform()->SetLocation(Vector::CreateVector(GetTransform()->GetLocation().X, GetTransform()->GetLocation().Y + (-RocketSpeed * DeltaSeconds), GetTransform()->GetLocation().Z));

	// should only trigger once per Class instance
	if(GetTransform()->GetLocation().Y <= -20 && !_HasBeenTriggered) 
	{
		// this is in a thread to avoid possible problems by deleting the actor and still try to do something with it right after (fool proof the system if you will)
		_HasBeenTriggered = true;
		std::thread t1([&]()
		{
			GameplayStatics::GetGameEngine()->RemoveActor(this);
		});
		t1.detach();
	}
}

void Missile::StartMovement()
{
	MySprite->PlayAnimation(true);
	CanMove = true;
}

