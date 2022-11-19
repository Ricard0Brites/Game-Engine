#pragma once
#include "object.h"
#include "..\Data\DataTypes.h"
#include "ActorComponents\SpriteComponent.h"

class Transform;
class SpriteComponent;

class Actor : Object
{
public:
	Actor();
	~Actor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(SDL_KeyCode KeyCode) override;

	virtual Transform* GetTransform();

	bool HasInit = false;

protected:
	Transform* MyTransform;
	SpriteComponent* MySprite;

};