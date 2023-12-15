#pragma once
#include "GameRules.h"

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 720

void GameRules::GetWindowDimentions(int& Width, int& Height)
{
	Width = WINDOWWIDTH;
	Height = WINDOWHEIGHT;
}

//player/spaceship
float GameRules::_PlayerMovementSpeed = 0.2f;

//Rocket
float GameRules::_RocketSpeed = 0.7f;
int GameRules::_RocketDamage = 1;
int GameRules::_TimeBetweenRocketSpawn = 200;

//Enemies
	//Loner
	float GameRules::_LonerSpeed = 0.1f;
		//Loner Projectile
		float GameRules::_LonerProjectileFiringInterval = 2000.f;
		float GameRules::_LonerProjectileSpeed = 0.1f;
	//Drone
	float GameRules::_DroneMovementSpeed = 0.15f;
	float GameRules::_DroneSineMovementAmplitude = 0.05f;
	//Asteroid
	float GameRules::_AsteroidFallingSpeed = 0.15f;

//level 
float  GameRules::_LevelMovementSpeed = 0.04f;
float GameRules::_EnemySpawnScreenDivisions = 9.f;
