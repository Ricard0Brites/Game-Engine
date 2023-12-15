#include "Actor.h"
#include "GameEngine.h"
#include "ActorComponents\SpriteComponent.h"
#include "Data\DataTypes.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	CollisionRadius = -1;
	IsLevelActor = true;
	IsPendingKill = false;	
}

Actor::Actor(Actor* Parent, const char* DisplayName) : Actor(Parent)
{
	ActorDisplayName = DisplayName;
}
Actor::~Actor()
{
	if (MySprite)
	{
		delete MySprite;
		MySprite = nullptr;
	}
	if (MyTransform)
	{
		delete MyTransform;
		MyTransform = nullptr;
	}
}

void Actor::Tick(float DeltaSeconds)
{
	if(IsPendingKill) return;
	if(MySprite)MySprite->Tick(DeltaSeconds);
	if (GetTransform()->GetLocation().Y > (GameplayStatics::GetScreenHeight() * 1.25f) || 
		GetTransform()->GetLocation().X > (GameplayStatics::GetScreenWidth() * 1.25f))
	{
		GameEngine* EngineRef = GameplayStatics::GetGameEngine();
		Validate(EngineRef,);
		EngineRef->RemoveActor(this);
	}
}

void Actor::AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	MySprite = new SpriteComponent(TexturePath, TileAmountX, TileAmountY, AnimationTimeInSeconds, ComponentOwner);
	CollisionRadius = max((float)MySprite->GetSpriteWidth(), (float)MySprite->GetSpriteHeight()) * 0.5f;
}

void Actor::OnCollisionStarted(const Actor* OtherActor)
{}

void Actor::BeginPlay()
{}

void Actor::OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue)
{}

void Actor::OnKeyPressed(InputKeyCodes KeyCode)
{}

void Actor::OnKeyReleased(InputKeyCodes KeyCode)
{}
