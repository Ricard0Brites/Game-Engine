#pragma once
#include "GameEngine.h"
#include "Components\XennonSpriteComponent.h"

class Player : public Actor
{
public:


	Player(Actor* Owner);
	~Player();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(InputKeyCodes KeyCode) override;

	virtual void OnKeyReleased(InputKeyCodes KeyCode) override;

	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) override;

	XennonStaticSpriteComponent* GetCustomSpriteComponent() { return (XennonStaticSpriteComponent*)MySprite; }

protected:
	bool bMoveDirection[4];//0-> up 1->left 2->down 3->right

private:
	bool _AnimStateManager;
	int _IdleShipAnimIndex = 4;
	
	bool _CanKeepShooting = false; 
	float _ShootingTimer = 0;
};