#pragma once
#include "Loner.h"
#include "GameEngine.h"
#include "../GameRules.h"
#include <thread>


Loner::Loner(Actor* Owner) : Actor(Owner)
{
	CollisionRadius = 100.f;
}

void Loner::BeginPlay()
{
	Actor::BeginPlay();
	AssignTexture("src/Sprites/LonerB.bmp", 4, 4, 2, this);
	GetSpriteComponent()->PlayAnimation(true);
}

void Loner::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
// 	GetTransform()->SetLocation(Vector::CreateVector(
// 		/*X*/ GetTransform()->GetLocation().X + (GameRules::GetEnemyMovementSpeed() * DeltaSeconds),
// 		/*Y*/ GetTransform()->GetLocation().Y, // falling speed
// 		/*Z*/ 0
// 	));

	// should only trigger once per Class instance
	if (GetTransform()->GetLocation().X > (float)(GameplayStatics::GetScreenWidth() + 10))
	{
		GameplayStatics::GetGameEngine()->RemoveActor(this);
	}
}

void Loner::AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	Actor::AssignTexture(TexturePath, TileAmountX, TileAmountY, AnimationTimeInSeconds, ComponentOwner);
}

SpriteComponent* Loner::GetSpriteComponent()
{
	return MySprite;
}

void Loner::OnCollisionStarted(const Actor* OtherActor)
{
	GameplayStatics::GetGameEngine()->RemoveActor(this);
}
