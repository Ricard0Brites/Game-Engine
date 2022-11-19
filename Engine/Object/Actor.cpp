#include "Actor.h"

Actor::Actor()
{
	MyTransform = new Transform;
	MySprite = new SpriteComponent;
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
