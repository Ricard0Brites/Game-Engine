#include "Missile.h"
#include "GameEngine.h"


Missile::Missile(Actor* Parent) :Actor(Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
}

Missile::~Missile()
{
	if (MyTransform) delete MyTransform;
	if (MySprite) delete MySprite;
}

void Missile::BeginPlay()
{

}

void Missile::Tick(float DeltaSeconds)
{
	if (MySprite) MySprite->Tick(DeltaSeconds);
}

