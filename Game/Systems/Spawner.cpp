#include "Spawner.h"
#include "GameEngine.h"
#include "Logger\Logger.h"
#include <stdlib.h>
#include <math.h>
#include <thread>

Spawner::Spawner()
{
}

Spawner::~Spawner()
{
	if(SpawnerThread) 
	{
		delete SpawnerThread;
	}
}

void Spawner::InitSpawner()
{
	SpawnerThread = new thread([&](){

		Spawn = true;
		while (true)
		{
			GameplayStatics::Delay(TimeBetweenWaves);
			TimeBetweenWaves = 3 * ((float)rand() / (float)RAND_MAX);

			switch (rand() % 6)
			{
			case 0:
				SpawnLoner();
				break;
			case 1:
				SpawnClone();
				break;
			case 2:
				SpawnDrone();
				break;
			case 3:
				SpawnAsteroid();
				break;
			case 4:
				SpawnRusher();
				break;
			default:
				break;
			}
		}

	});
	SpawnerThread->detach();
}

void Spawner::SpawnLoner()
{
	LOG("SpawnLoner", 3);
}

void Spawner::SpawnClone()
{
	LOG("SpawnClone", 3);
}

void Spawner::SpawnDrone()
{
	LOG("SpawnDrone", 3);
}

void Spawner::SpawnAsteroid()
{
	LOG("SpawnAsteroid", 3);
}

void Spawner::SpawnRusher()
{
	LOG("SpawnRusher", 3);
}
