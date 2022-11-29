#pragma once
#include "Actor.h"

class Missile : public Actor
{

public:

	Missile(Actor* Owner);
	~Missile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


protected:

};