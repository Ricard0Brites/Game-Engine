#include "PowerUp.h"
#include "GameRules.h"
#include "Player.h"

void PowerUp::BeginPlay()
{
	Actor::BeginPlay();
	AssignTexture("src/Sprites/PUWeapon.bmp",4,2,1,this);
	MySprite->PlayAnimation(1);
}

void PowerUp::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	GetTransform()->SetLocation(GetTransform()->GetLocation() + (Vector::CreateVector(0,1,0) * GameRules::GetLevelMovementSpeed()));
}

void PowerUp::OnCollisionStarted(const Actor* OtherActor)
{
	if (Player* PlayerRef = dynamic_cast<Player*>(const_cast<Actor*>(OtherActor)))
	{
		CollisionRadius = -1;

		PlayerRef->CreateCompanion();

		GameEngine* EngineRef = GameplayStatics::GetGameEngine();
		Validate(EngineRef,);

		EngineRef->RemoveActor(this);
	}
}

