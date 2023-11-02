#pragma once
#include "object.h"
#include "..\Data\DataTypes.h"
#include "ActorComponents\SpriteComponent.h"
#include "ActorComponents\CollisionComponent.h"


class Transform;
class SpriteComponent;
class Vector;

class Actor : public Object, public CollisionComponent
{
public:
	Actor(Actor* Owner);
	~Actor();

	virtual void Tick(float DeltaSeconds) override;

	Transform* GetTransform() { return MyTransform; }

	Actor* GetOwner() { return Owner; }

	bool HasInit = false;

	virtual void AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner);
	
	SpriteComponent* GetSpriteComponent() { return MySprite; }

	int CollisionRadius = -1;

	virtual void OnCollisionStarted(const Actor* OtherActor) override;

	virtual void BeginPlay() override;

	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) override;

	virtual void OnKeyPressed(InputKeyCodes KeyCode) override;

	virtual void OnKeyReleased(InputKeyCodes KeyCode) override;

protected:
	Transform* MyTransform;
	SpriteComponent* MySprite;

	
	//nullptr id this object is independent
	Actor* Owner = nullptr;

};