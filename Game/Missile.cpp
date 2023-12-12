#include "Missile.h"
#include "GameEngine.h"
#include "GameRules.h"
#include "SDL_timer.h"

#include <thread>

Missile::Missile(Actor* Parent) : Actor(Parent)
{
	RocketSpeed = GameRules::GetRocketMovementSpeed();
	RocketDamage = GameRules::GetRocketDamage();
	IsLevelActor = false;
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
	if(GetTransform()->GetLocation().Y <= -20) 
	{
		GameplayStatics::GetGameEngine()->RemoveActor(this);
	}
}

void Missile::StartMovement()
{
	MySprite->PlayAnimation(true);
	CanMove = true;
}

