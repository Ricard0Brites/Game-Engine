#pragma once
#include "GameEngine.h"



class Enemy : public Actor
{
public:

	Enemy(Actor* Owner);
	~Enemy();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

private:
bool _HasBeenTriggered = false;

};