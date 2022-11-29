#include "Enemy.h"
#include "GameEngine.h"
#include "GameRules.h"


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
	GetTransform()->SetLocation(Vector::CreateVector(
	/*X*/ GetTransform()->GetLocation().X + (GameRules::GetEnemyMovementSpeed() * DeltaSeconds),
	/*Y*/ GetTransform()->GetLocation().Y, // falling speed
	/*Z*/ 0
	));
}