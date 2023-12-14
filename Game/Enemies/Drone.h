#pragma once
#include "GameEngine.h"

class Drone : public Actor
{
public:
	Drone(Actor* Owner);
	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;

	float MovementDirectionX = 1;

private: 
	float TimeCounter = 0;	
	float MovementDirectionY = 1;
};

