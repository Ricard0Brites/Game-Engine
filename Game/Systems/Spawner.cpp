#include "Spawner.h"
#include "GameEngine.h"
#include "Logger\Logger.h"
#include <stdlib.h>
#include <math.h>
#include <thread>
#include "..\Enemies\Loner.h"
#include "..\Enemies\Drone.h"
#include "..\Enemies\Asteroid.h"
#include "..\Enemies\Rusher.h"
#include "..\GameRules.h"

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
	EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );
	SpawnerThread = new std::thread([&](){

		Spawn = true;
		while (true)
		{
			GameplayStatics::Delay(2);

			switch (rand() % 5)
			{
			case 0:
				SpawnLoner();
				break;
			case 1:
				SpawnDrone();
				break;
			case 2:
				SpawnAsteroid();
				break;
			case 3:
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
	int NumOfEnemiesToSpawn = (rand() % 11);
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
			Loner* Enemy = EngineRef->CreateActor<Loner>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			(float)Spacing * i,
			0,
			0
			));
		}
}

void Spawner::SpawnDrone()
{
	int NumOfEnemiesToSpawn = (rand() % 11);
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	int YSpawnLocation = rand() % (GameplayStatics::GetScreenHeight() / 2) + 1;
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
			Drone* Enemy = EngineRef->CreateActor<Drone>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			40.f * i,
			(float)YSpawnLocation,
			0.f
			));
			Enemy->Offset = i * (1000.f/NumOfEnemiesToSpawn);
		}
}

void Spawner::SpawnAsteroid()
{
	int NumOfEnemiesToSpawn = (rand() % 11);
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	int YSpawnLocation = rand() % (GameplayStatics::GetScreenHeight() / 4) + 1;
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
 			Asteroid* Enemy = EngineRef->CreateActor<Asteroid>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			(rand() % GameplayStatics::GetScreenWidth() * 0.75f) + ((GameplayStatics::GetScreenWidth() * 0.5f) * 0.25f),
			(float)YSpawnLocation,
			0
			));
			Enemy->SetAsteroidType(0);
		}
}

void Spawner::SpawnRusher()
{
	int NumOfEnemiesToSpawn = (rand() % 11);
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
	{
		Rusher* Enemy = EngineRef->CreateActor<Rusher>(nullptr);
	}
}
