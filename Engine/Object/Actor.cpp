#include "Actor.h"
#include "../GameEngine.h"
#include "ActorComponents\SpriteComponent.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	CollisionRadius = 0;

	
}

Actor::~Actor()
{
	if(MyTransform) delete MyTransform;
	if(MySprite) delete MySprite;
}

void Actor::Tick(float DeltaSeconds)
{
	if(MySprite != nullptr)MySprite->Tick(DeltaSeconds);
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
