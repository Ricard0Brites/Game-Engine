#pragma once
#include "object.h"
#include "Data\DataTypes.h"
#include "ActorComponents\SpriteComponent.h"
#include "ActorComponents\CollisionComponent.h"

class Transform;
class SpriteComponent;
class Vector;

class Actor : public Object, public CollisionComponent
{
public:
	Actor(Actor* Parent);
	Actor(Actor* Parent, const char* DisplayName);
	~Actor();

	virtual void Tick(float DeltaSeconds) override;

	Transform* GetTransform() { return MyTransform; }

	Actor* GetOwner() { return Owner; }
	
	SpriteComponent* GetSpriteComponent() { return MySprite; }

	bool HasInit = false, IsPendingKill = false;
	int CollisionRadius = -1;

	virtual void AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner);

	virtual void OnCollisionStarted(const Actor* OtherActor) override;

	virtual void BeginPlay() override;

	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) override;

	virtual void OnKeyPressed(InputKeyCodes KeyCode) override;

	virtual void OnKeyReleased(InputKeyCodes KeyCode) override;

	std::string ActorDisplayName = "";
protected:
	Transform* MyTransform;
	SpriteComponent* MySprite;

	//nullptr id means this object is independent
	Actor* Owner = nullptr;
	int a = 0;

};