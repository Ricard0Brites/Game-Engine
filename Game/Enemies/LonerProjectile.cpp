#include "LonerProjectile.h"
#include "../GameRules.h"


LonerProjectile::LonerProjectile(Actor* Owner) : Actor(Owner)
{

}

void LonerProjectile::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	if(IsPendingKill) return;
	Vector CurrentLocation = GetTransform()->GetLocation();
	GetTransform()->SetLocation(CurrentLocation + (ProjectileMovementDirection * (GameRules::GetLonerProjectileSpeed() * DeltaSeconds)));
}

void LonerProjectile::BeginPlay()
{
	Actor::BeginPlay();
	AssignTexture("src/Sprites/EnWeap6.bmp", 8, 1, 1, this);
	GetSpriteComponent()->PlayAnimation(true);

}

void LonerProjectile::OnCollisionStarted(const Actor* OtherActor)
{
	
}
