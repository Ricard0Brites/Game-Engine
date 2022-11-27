#pragma once
#include "object.h"
#include "..\Data\DataTypes.h"
#include "ActorComponents\SpriteComponent.h"

class Transform;
class SpriteComponent;
class Vector;

class Actor : Object
{
public:
	Actor(Actor* Owner);
	~Actor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(InputKeyCodes KeyCode) override;

	virtual void OnKeyReleased(InputKeyCodes KeyCode) override;

	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) override;


	virtual Transform* GetTransform();

	Actor* GetOwner() { return Owner; }

	bool HasInit = false;

	void AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds);
	
	SpriteComponent* GetSpriteComponent() { return MySprite; }

protected:
	Transform* MyTransform;
	SpriteComponent* MySprite;
	
	//nullptr id this object is independent
	Actor* Owner = nullptr;

};