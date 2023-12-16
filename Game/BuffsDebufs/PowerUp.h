#pragma once
#include "GameEngine.h"

class PowerUp : public Actor
{
	
public:

	PowerUp(Actor* Owner);
	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;
};

