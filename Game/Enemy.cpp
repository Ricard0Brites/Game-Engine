#include "Enemy.h"
#include "GameEngine.h"


Enemy::Enemy(Actor* Parent):Actor(Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
}

Enemy::~Enemy()
{
	if (MyTransform) delete MyTransform;
	if (MySprite) delete MySprite;
}

void Enemy::BeginPlay()
{

}

void Enemy::Tick(float DeltaSeconds)
{
	if (MySprite) MySprite->Tick(DeltaSeconds);

	//MySprite->SetLocation((MySprite->Gettransform()->GetLocation() += Vector::CreateVector(0, 0.001f, 0)), nullptr);
}

