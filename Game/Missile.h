#pragma once
#include "GameEngine.h"

class Missile : public Actor
{

public:

	Missile(Actor* Owner);
	~Missile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void StartMovement();

protected:
	bool CanMove = false;
	float RocketSpeed;
	int RocketDamage;
};