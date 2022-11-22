#include "Actor.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
	
	//example of the sprite component
	MySprite = new SpriteComponent("C:/Users/Ricardo/Desktop/drone.bmp", 8, 2, 2);
	MySprite->SetScale(Vector::CreateVector(5,5,0), Owner);
	MySprite->SetLocation(Vector::CreateVector(100,100,0), Owner);
	MySprite->PlayAnimation(true);
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
	if(MySprite) MySprite->Tick(DeltaSeconds);
}

void Actor::OnKeyPressed(SDL_KeyCode KeyCode)
{
	
}

Transform* Actor::GetTransform()
{
	return MyTransform;
}