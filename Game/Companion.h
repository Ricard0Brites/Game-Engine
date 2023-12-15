#pragma once
#include "GameEngine.h"
class Companion : public Actor
{
public: 
	
	Companion(Actor* Owner);
	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;

};

