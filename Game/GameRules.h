#pragma once

class GameRules
{
public:
	static float GetPlayerMovementSpeed() { return _PlayerMovementSpeed; }
	
	//Rocket
	static float GetRocketMovementSpeed() { return _RocketSpeed; }
	static int GetRocketDamage() { return _RocketDamage; }
	static int GetTimeBetweenShots() { return _TimeBetweenRocketSpawn; }

	//Enemies
		//Loner
		static float GetLonerMovementSpeed() { return _LonerSpeed; }
		static float GetLonerProjectileFiringInterval() { return _LonerProjectileFiringInterval; }
			// Loner Projectile
			static float GetLonerProjectileSpeed() { return _LonerProjectileSpeed; }
		//Drone
		static float GetDroneMovementSpeed() { return _DroneMovementSpeed;}
		static float GetDroneMovementAmplitude() { return _DroneSineMovementAmplitude; }
		
		//Asteroid
		static float GetAsteroidFallingSpeed() { return _AsteroidFallingSpeed; }
	//level
	static float GetLevelMovementSpeed() { return _LevelMovementSpeed; }
	static float GetNumberOfSpawns() { return _EnemySpawnScreenDivisions; }
	
	//Window
	static void GetWindowDimentions(int &Width, int &Height);

private:
	//Spaceship/Player
	static float _PlayerMovementSpeed;

	//Rockets/Missiles
	static float _RocketSpeed;
	static int _RocketDamage;
	static int _TimeBetweenRocketSpawn;

	//enemies
		//Loner
		static float _LonerSpeed;
		static float _LonerProjectileSpeed;
			//Loner Projectile
			static float _LonerProjectileFiringInterval;
		//Drone
		static float _DroneMovementSpeed;
		static float _DroneSineMovementAmplitude;
		
		//Asteroid
		static float _AsteroidFallingSpeed;
	//Level
	static float _LevelMovementSpeed; // this is the vertical movement speed of the whole game (multiply this for paralax)
	static float _EnemySpawnScreenDivisions;
};