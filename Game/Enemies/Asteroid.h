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

	// 0 stone, 1 rock, 2 Metal
	void SetAsteroidType(int Type) { AsteroidType = Type; }
	void SetAsteroidState(int State) {AsteroidState = State; }
	void SetMovementDirection(Vector Direction) { FallingDirection = Direction; }
	virtual void Tick(float DeltaSeconds) override;

private:
	AnimationParameters Asteroids[3];
	unsigned int AsteroidType = 2, AsteroidState = 0, TypeTwoAsteroidHitCount = 0;
	Vector FallingDirection = Vector::CreateVector(0,1,0);
	bool IsInvincible = false;
	void SpawnChildAsteroids();
};