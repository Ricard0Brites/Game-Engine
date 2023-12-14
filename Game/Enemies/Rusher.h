#pragma once
#include "GameEngine.h"

class Rusher : public Actor
{
public:

	Rusher(Actor* Owner);

	virtual void BeginPlay() override;
	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	GameEngine* _EngineRef = nullptr;
	int WindowWidth, WindowHeight;
	bool MovementDirection = false;
};

