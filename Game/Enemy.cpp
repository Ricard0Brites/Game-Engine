#include "Enemy.h"
#include "GameEngine.h"


Enemy::Enemy(Actor* Parent):Actor(Parent)
{
}

Enemy::~Enemy()
{

}

void Enemy::BeginPlay()
{
	Actor::BeginPlay();
}

void Enemy::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	
}

