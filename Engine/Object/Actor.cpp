#include "Actor.h"

Actor::Actor()
{
	MyTransform = new Transform;
}

Actor::~Actor()
{
	if(MyTransform) delete MyTransform;
}

void Actor::BeginPlay()
{
	
}

void Actor::Tick(float DeltaSeconds)
{
	
}

void Actor::OnKeyPressed(SDL_KeyCode KeyCode)
{
	
}

Transform* Actor::GetTransform()
{
	return MyTransform;
}
