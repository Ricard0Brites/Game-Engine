#include "Companion.h"
#include "Player.h"
#include <thread>

Companion::Companion(Actor* Owner) : Actor(Owner)
{

}

void Companion::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
}
void Companion::BeginPlay()
{
	AssignTexture("src/Sprites/clone1.bmp", 4,4,1,this);
	MySprite->PlayAnimation(1);
}

void Companion::OnCollisionStarted(const Actor* OtherActor)
{
	if (dynamic_cast<const Player*>(OtherActor))
	{
		CollisionRadius = -1;
		DestroySpriteComponent();
		AssignTexture("src/Sprites/CloneDeath.bmp", 4, 1, 1, this);
		MySprite->PlayAnimation(0);
		std::thread t1([&]() {
			GameplayStatics::Delay(1);
			GameEngine* EngineRef = GameplayStatics::GetGameEngine();
			Validate(EngineRef,);
			EngineRef->RemoveActor(this);
			});
			t1.detach();
	}
}

