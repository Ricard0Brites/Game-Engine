#include "Shield.h"
#include "..\Player.h"
#include "..\GameRules.h"

void Shield::BeginPlay()
{
	Actor::BeginPlay();
	AssignTexture("src/Sprites/PUShield.bmp", 4, 2, 1, this);
	MySprite->PlayAnimation(1);
}


void Shield::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);

	GetTransform()->SetLocation(GetTransform()->GetLocation() + (Vector::CreateVector(0,1,0) * GameRules::GetLevelMovementSpeed()));
}

void Shield::OnCollisionStarted(const Actor* OtherActor)
{
	if (Player* PlayerRef = dynamic_cast<Player*>(const_cast<Actor*>(OtherActor)))
	{	
		CollisionRadius = -1;
		GameEngine* EngineRef = GameplayStatics::GetGameEngine();
		Validate(EngineRef,);
		PlayerRef->AddHealth(1);
		EngineRef->RemoveActor(this);
	}
}