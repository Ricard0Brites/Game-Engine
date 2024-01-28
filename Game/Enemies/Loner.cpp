#pragma once
#include "Loner.h"
#include "GameEngine.h"
#include "../GameRules.h"
#include "LonerProjectile.h"


Loner::Loner(Actor* Owner) : Actor(Owner)
{
}

Loner::~Loner()
{
	Actor::~Actor();
}

void Loner::BeginPlay()
{
	Actor::BeginPlay();
	AssignTexture("src/Sprites/LonerB.bmp", 4, 4, 2, this);
	GetSpriteComponent()->PlayAnimation(true);
	
	GameRules::GetWindowDimentions(_WindowWidth, _WindowHeight);
	_GameEngineRef = GameplayStatics::GetGameEngine();
	Validate(_GameEngineRef,);
}

void Loner::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	GetTransform()->SetLocation(Vector::CreateVector(
		/*X*/ GetTransform()->GetLocation().X + (GameRules::GetLonerMovementSpeed() * DeltaSeconds),
		/*Y*/ GetTransform()->GetLocation().Y, // falling speed
		/*Z*/ 0
	));
	
	TimerCounter += DeltaSeconds;
	if(TimerCounter > GameRules::GetLonerProjectileFiringInterval() && !IsPendingKill)
	{
		SpawnProjectile();
		TimerCounter = 0;
	}
}

SpriteComponent* Loner::GetSpriteComponent()
{
	return MySprite;
}

void Loner::OnCollisionStarted(const Actor* OtherActor)
{
	GameplayStatics::GetGameEngine()->RemoveActor(this);
}

void Loner::SpawnProjectile()
{
	if(IsPendingKill) return;
	if(!this || !HasInit) return;
	if(!MyTransform) return;

	bool XIsInBounds = GetTransform()->GetLocation().X >= 0 && GetTransform()->GetLocation().X < _WindowWidth;
	bool YIsInBounds = GetTransform()->GetLocation().Y >= 0 && GetTransform()->GetLocation().Y < _WindowHeight;

	if (XIsInBounds && YIsInBounds)
	{
		Validate(_GameEngineRef, );

		LOG("Spawning Loner Projectile", 1);

		LonerProjectile* Projectile = _GameEngineRef->CreateActor<LonerProjectile>(nullptr);

		Vector TargetLocation, OriginLocation;
		TargetLocation = _GameEngineRef->GetPlayer()->GetTransform()->GetLocation(); // player location
		OriginLocation = GetTransform()->GetLocation(); // Loner Location

		Projectile->SetProjectileDirection(GameplayStatics::NormalizeVector(TargetLocation - OriginLocation));
		Vector LocationCache = GetTransform()->GetLocation();
		Projectile->GetTransform()->SetLocation(Vector::CreateVector(LocationCache.X + (MySprite->GetSpriteWidth() / 2), LocationCache.Y + MySprite->GetSpriteHeight(), 0));
	}
}