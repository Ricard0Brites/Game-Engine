#pragma once
#include "GameEngine.h"
class Shield : public Actor
{
	
public:
	Shield(Actor* Owner);
	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;

};

