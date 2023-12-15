#pragma once
#include <iostream>
#include <thread>

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
	void SpawnClone();
	void SpawnDrone();
	void SpawnAsteroid();
	void SpawnRusher();

	GameEngine* EngineRef = nullptr;
	std::thread* SpawnerThread = nullptr;
};

