#pragma once
#include "object.h"
#include "..\Data\DataTypes.h"
#include "ActorComponents\SpriteComponent.h"

class Transform;
class SpriteComponent;

class Actor : Object
{
public:
	Actor(Actor* Owner);
	~Actor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(SDL_KeyCode KeyCode) override;

	virtual Transform* GetTransform();

	Actor* GetOwner() { return Owner; }

	bool HasInit = false;

protected:
	Transform* MyTransform;
	SpriteComponent* MySprite;
	
	//nullptr id this object is independent
	Actor* Owner = nullptr;

};