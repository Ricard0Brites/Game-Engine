#pragma once
#include "GameEngine.h"

class Loner : public Actor
{
public:
	Loner(Actor* Owner);
	~Loner();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void AssignTexture(std::string TexturePath, int TileAmountX, int TileAmountY, float AnimationTimeInSeconds, Actor* ComponentOwner) override;

	virtual Transform* GetTransform() override;

	SpriteComponent* GetSpriteComponent();

private:
	
	bool _HasBeenTriggered = false;
};