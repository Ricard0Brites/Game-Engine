#include "Rusher.h"
#include "..\Player.h"
#include "..\GameRules.h"

Rusher::Rusher(Actor* Owner) : Actor(Owner)
{

}

void Rusher::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);

	GetTransform()->SetLocation(Vector::CreateVector(GetTransform()->GetLocation().X, GetTransform()->GetLocation().Y + (GameRules::GetPlayerMovementSpeed() * 2 * DeltaSeconds), 0));
}

void Rusher::BeginPlay()
{
	Actor::BeginPlay();

	if (GameEngine* EngineRef = GameplayStatics::GetGameEngine())
	{
		_EngineRef = EngineRef;
	}

	AssignTexture("src/Sprites/rusher.bmp", 4, 6, 1.f, this);
	GetSpriteComponent()->PlayAnimation(1);

	MovementDirection = roundf((float)rand() / (float)RAND_MAX);
	GameRules::GetWindowDimentions(WindowWidth, WindowHeight);
	
	Vector SpawnLocation = Vector::CreateVector(
	(WindowWidth / GameRules::GetNumberOfSpawns()) * (round(((float)rand() / (float)RAND_MAX) * 9)),
	MovementDirection ? WindowWidth : 0.f - MySprite->GetSpriteHeight(),
	0.f);
}

void Rusher::OnCollisionStarted(const Actor* OtherActor)
{
	if(dynamic_cast<const Player*>(OtherActor))
	{
		_EngineRef->RemoveActor(this);
	}
}