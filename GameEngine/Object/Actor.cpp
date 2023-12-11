#include "Actor.h"
#include "../GameEngine.h"
#include "ActorComponents\SpriteComponent.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	CollisionRadius = 0;
	IsPendingKill = false;	
}

Actor::Actor(Actor* Parent, const char* DisplayName) : Actor(Parent)
{
	ActorDisplayName = DisplayName;
}

Actor::~Actor()
{
	delete MyTransform;
	delete MySprite;
}

void Actor::Tick(float DeltaSeconds)
{
	if(MySprite)MySprite->Tick(DeltaSeconds);
}

void Actor::AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	MySprite = new SpriteComponent(TexturePath, TileAmountX, TileAmountY, AnimationTimeInSeconds, ComponentOwner);
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
