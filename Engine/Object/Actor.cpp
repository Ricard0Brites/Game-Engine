#include "Actor.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	
	//example of the sprite component
	//MySprite = new SpriteComponent("F:/Year3/Game-Engine/Engine/Temp/graphics/drone.bmp", 8, 2, 2);
	//MySprite->PlayAnimation(false);
}

Actor::~Actor()
{
	if(MyTransform) delete MyTransform;
	if(MySprite) delete MySprite;
}

void Actor::BeginPlay()
{
	
}

void Actor::Tick(float DeltaSeconds)
{
	MySprite->Tick(DeltaSeconds);
}

void Actor::OnKeyPressed(SDL_KeyCode KeyCode)
{
	
}

Transform* Actor::GetTransform()
{
	return MyTransform;
}