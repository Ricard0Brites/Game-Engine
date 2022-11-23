#include "Actor.h"

Actor::Actor(Actor* Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
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

void Actor::AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds)
{
	MySprite = new SpriteComponent(TexturePath, TileAmountX, TileAmountY, AnimationTimeInSeconds);
}
