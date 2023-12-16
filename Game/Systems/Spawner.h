#pragma once
#include <iostream>
#include <thread>
#include "GameEngine.h"

using namespace std;

class thread;

class Spawner
{
public:
		Spawner();
		~Spawner();

	void InitSpawner();
	bool Spawn = false;
private:
	void SpawnLoner();
	void SpawnDrone();
	void SpawnAsteroid();
	void SpawnRusher();
	void SpawnShieldPowerUp();
	void SpawnWeaponPowerUp();

	GameEngine* EngineRef = nullptr;
	std::thread* SpawnerThread = nullptr;
};

