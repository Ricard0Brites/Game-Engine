#include "Rusher.h"
#include "..\Player.h"

Rusher::Rusher(Actor* Owner) : Actor(Owner)
{

}

void Rusher::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
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
}

void Rusher::OnCollisionStarted(const Actor* OtherActor)
{
	if(dynamic_cast<const Player*>(OtherActor))
	{
		_EngineRef->RemoveActor(this);
	}
}