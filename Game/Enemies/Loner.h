#pragma once
#include "GameEngine.h"

class Loner : public Actor
{
public:
	Loner(Actor* Owner);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	SpriteComponent* GetSpriteComponent();

	virtual void OnCollisionStarted(const Actor* OtherActor) override;
	
private:
	void SpawnProjectile();
	int _WindowWidth = 0, _WindowHeight = 0;
	GameEngine *_GameEngineRef = nullptr;
	
};