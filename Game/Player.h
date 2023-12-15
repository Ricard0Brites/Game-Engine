#pragma once
#include "GameEngine.h"
#include "Components\XennonSpriteComponent.h"
#include "Companion\Companion.h"

#define MAXFLOAT 8589934591.f

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

	virtual void OnCollisionStarted(const Actor* OtherActor) override;

	void CreateCompanion();
	void DestroyCompanion();
	void DestroyCompanion(Companion* Ref);

	void AddHealth(int LifestoAdd) { _HealthPoints += 2 * LifestoAdd; }

protected:
	bool bMoveDirection[4];//0-> up 1->left 2->down 3->right
	void DestroyPlayer();
	

private:
	bool _AnimStateManager;
	unsigned short int _IdleShipAnimIndex = 4;
	bool _CanKeepShooting = false; 
	float _ShootingTimer = MAXFLOAT;
	bool _HasDied = false;
	unsigned short int _HealthPoints = 5;
	Companion *Companion1 = nullptr, *Companion2 = nullptr;
};