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
		
	//level
	static float GetLevelMovementSpeed() { return _LevelMovementSpeed; }
	
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
		static float _LonerProjectileFiringInterval;

	//Level
	static float _LevelMovementSpeed; // this is the vertical movement speed of the whole game (multiply this for paralax)
};