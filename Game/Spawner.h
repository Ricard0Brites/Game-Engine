#pragma once
#include <iostream>

namespace std { class thread; }

using namespace std;

class Spawner
{
public:
		Spawner();
		~Spawner();

	void InitSpawner();
	bool Spawn = false;
private:
	void SpawnLoner();
	void SpawnClone();
	void SpawnDrone();
	void SpawnAsteroid();
	void SpawnRusher();

	thread* SpawnerThread = nullptr;
	float TimeBetweenWaves = 3.f;
};

