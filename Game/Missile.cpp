#include "Missile.h"
#include "GameEngine.h"
#include "GameRules.h"
#include "SDL_timer.h"

#include <thread>

Missile::Missile(Actor* Parent) : Actor(Parent)
{
	RocketSpeed = GameRules::GetRocketMovementSpeed();
	RocketDamage = GameRules::GetRocketDamage();
	IsLevelActor = false;
}

void Missile::BeginPlay()
{
	Actor::BeginPlay();

	AssignTexture("src/Sprites/missile1.bmp", 2, 1, 0.5f, this);
	GetSpriteComponent()->SetScale(Vector::CreateVector(1, 1, 1), nullptr);
	GetSpriteComponent()->PlayAnimation(true);
	StartMovement();
}

void Missile::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	if (!CanMove || Exploded) 
		return;
	GetTransform()->SetLocation(Vector::CreateVector(GetTransform()->GetLocation().X, GetTransform()->GetLocation().Y + (-RocketSpeed * DeltaSeconds), GetTransform()->GetLocation().Z));

	// should only trigger once per Class instance
	if(GetTransform()->GetLocation().Y <= -20) 
	{
		GameplayStatics::GetGameEngine()->RemoveActor(this);
	}
}

void Missile::StartMovement()
{
	MySprite->PlayAnimation(true);
	CanMove = true;
}

void Missile::OnCollisionStarted(const Actor* OtherActor)
{
	if(Exploded)
		return;
	Exploded = true;
	CollisionRadius = -1;
	delete MySprite;
	MySprite = nullptr;
	MySprite = new SpriteComponent("src/Sprites/explode64.bmp", 5, 2, 1.f, this);
	MySprite->SetLocation(Vector::CreateVector((float)(-MySprite->GetSpriteWidth() * 0.6f), (float)(-MySprite->GetSpriteHeight() * 0.6f), 0), nullptr);
	MySprite->PlayAnimation(false);

	// destroy actor
	thread([&]()
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if(!MySprite)
				return;
			MySprite->StopAnimation();
			GameplayStatics::GetGameEngine()->RemoveActor(this);
		}).detach();
}

