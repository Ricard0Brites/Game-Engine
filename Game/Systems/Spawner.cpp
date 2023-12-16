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
#include "..\BuffsDebufs\PowerUp.h"
#include "..\BuffsDebufs\Shield.h"

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

			switch (rand() % 7)
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
			case 4:
				SpawnWeaponPowerUp();
				break;
			case 5:
				SpawnShieldPowerUp();
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
	int NumOfEnemiesToSpawn = (rand() % 10)+1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	int YLocation = (rand() % (GameplayStatics::GetScreenHeight() / 3));
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
			Loner* Enemy = EngineRef->CreateActor<Loner>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			-64.f * (i + 1),
			(float)YLocation,
			0
			));
		}
}

void Spawner::SpawnDrone()
{
	int NumOfEnemiesToSpawn = (rand() % 10)+1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	int YSpawnLocation = rand() % (GameplayStatics::GetScreenHeight() / 2) + 1;
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
			Drone* Enemy = EngineRef->CreateActor<Drone>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			-40.f * (i + 1),
			(float)YSpawnLocation,
			0.f
			));
			Enemy->Offset = i * (1000.f/NumOfEnemiesToSpawn);
		}
}

void Spawner::SpawnAsteroid()
{
	int NumOfEnemiesToSpawn = (rand() % 4)+1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	int YSpawnLocation = rand() % (GameplayStatics::GetScreenHeight() / 4);
		for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
		{
 			Asteroid* Enemy = EngineRef->CreateActor<Asteroid>(nullptr);
			Enemy->GetTransform()->SetLocation(Vector::CreateVector(
			(rand() % (int)(GameplayStatics::GetScreenWidth() * 0.75f)) + (int)(GameplayStatics::GetScreenWidth() * 0.125f),
			-128.f,
			0
			));
			Enemy->SetAsteroidType(rand() % 3);
		}
}

void Spawner::SpawnRusher()
{
	int NumOfEnemiesToSpawn = (rand() % 10) + 1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	for (int i = 0; i < NumOfEnemiesToSpawn; ++i)
	{
		Rusher* Enemy = EngineRef->CreateActor<Rusher>(nullptr);
	}
}

void Spawner::SpawnShieldPowerUp()
{
	int NumOfEnemiesToSpawn = (rand() % 10)+1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	PowerUp* Enemy = EngineRef->CreateActor<PowerUp>(nullptr);
	Enemy->GetTransform()->SetLocation(Vector::CreateVector((float)Spacing, -128.f, 0));
}

void Spawner::SpawnWeaponPowerUp()
{
	int NumOfEnemiesToSpawn = (rand() % 10)+1;
	int Spacing = GameplayStatics::GetScreenWidth() / NumOfEnemiesToSpawn;
	Shield* Enemy = EngineRef->CreateActor<Shield>(nullptr);
	Enemy->GetTransform()->SetLocation(Vector::CreateVector((float)Spacing, -128.f, 0));
}
