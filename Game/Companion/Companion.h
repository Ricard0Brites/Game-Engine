#pragma once
#include "GameEngine.h"
class Companion : public Actor
{
public: 
	
	Companion(Actor* Owner);
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;

	private:
	bool AllowDestroy = false;
	float TimerCounter = 0;
	class Player* PlayerRef = nullptr;

};

