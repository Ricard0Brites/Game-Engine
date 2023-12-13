#pragma once
#include "GameEngine.h"
#include <iostream>

using namespace std;

struct AnimationParameters
{
public:
	string Path = "";
	int TileX = 0, TileY = 0;
	float AnimationTime = 0;
};

class Asteroid : public Actor
{
public:
	Asteroid(Actor* Parent);

	virtual void BeginPlay() override;

	virtual void OnCollisionStarted(const Actor* OtherActor) override;

private:
	  AnimationParameters Asteroids[9];
};

