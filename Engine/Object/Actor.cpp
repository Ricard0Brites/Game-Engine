#include "Actor.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	MySprite = new SpriteComponent("F:/Year3/Game-Engine/Engine/Temp/graphics/drone.bmp", 8, 2);
	LOG("WARNING: Remove the instance of the sprite component after testing is complete. \nThis can be located at:", 2);EXECUTIONLOG;
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
