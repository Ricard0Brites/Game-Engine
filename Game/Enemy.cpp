#include "Enemy.h"
#include "GameEngine.h"
#include "GameRules.h"
#include <thread>


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

	// should only trigger once per Class instance
	if(GetTransform()->GetLocation().X > (float)(GameplayStatics::GetScreenWidth() + 10) && !_HasBeenTriggered) 
	{
		// this is in a thread to avoid possible problems by deleting the actor and still try to do something with it right after (fool proof the system if you will)
		_HasBeenTriggered = true;
		std::thread t1([&]()
		{
			GameplayStatics::GetGameEngine()->RemoveActor(this);
		});
		t1.detach();
	}
}