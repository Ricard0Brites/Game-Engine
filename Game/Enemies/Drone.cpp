#include "Drone.h"
#include "..\GameRules.h"

Drone::Drone(Actor* Owner) : Actor(Owner)
{

}

void Drone::BeginPlay()
{
	Actor::BeginPlay();

	AssignTexture("src/Sprites/drone.bmp", 8, 2, 1, this);
	GetSpriteComponent()->PlayAnimation(1);
	TimeCounter += Offset;
}

void Drone::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	TimeCounter += DeltaSeconds;

	Vector currentLocation = GetTransform()->GetLocation();
	GetTransform()->SetLocation(Vector::CreateVector(
	(currentLocation.X + (GameRules::GetDroneMovementSpeed() * DeltaSeconds)) * MovementDirectionX, 
	currentLocation.Y + (((sin(TimeCounter * (1.f/120.f)) * GameRules::GetDroneMovementAmplitude()) * DeltaSeconds)) * MovementDirectionY,
	0));
}

void Drone::OnCollisionStarted(const Actor* OtherActor)
{
	if(dynamic_cast<const Actor*>(OtherActor))
	{
		GameplayStatics::GetGameEngine()->RemoveActor(this);
	}
}