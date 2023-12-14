#include "Drone.h"

Drone::Drone(Actor* Owner) : Actor(Owner)
{

}

void Drone::BeginPlay()
{
	Actor::BeginPlay();
}

void Drone::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
}

void Drone::OnCollisionStarted(const Actor* OtherActor)
{
	
}