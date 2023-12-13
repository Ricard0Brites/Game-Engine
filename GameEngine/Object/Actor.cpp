#include "Actor.h"
#include "../GameEngine.h"
#include "ActorComponents\SpriteComponent.h"

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
	delete MyTransform;
	MyTransform = nullptr;
	delete MySprite; 
	MySprite = nullptr;
}

void Actor::Tick(float DeltaSeconds)
{
	if(IsPendingKill) return;
	if(MySprite)MySprite->Tick(DeltaSeconds);
}

void Actor::AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	MySprite = new SpriteComponent(TexturePath, TileAmountX, TileAmountY, AnimationTimeInSeconds, ComponentOwner);
	CollisionRadius = max((float)MySprite->GetSpriteWidth(), (float)MySprite->GetSpriteHeight()) * 0.5f;
}

void Actor::OnCollisionStarted(const Actor* OtherActor)
{

}

void Actor::BeginPlay()
{

}

void Actor::OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue)
{

}

void Actor::OnKeyPressed(InputKeyCodes KeyCode)
{

}

void Actor::OnKeyReleased(InputKeyCodes KeyCode)
{

}
