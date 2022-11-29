#pragma once
class GameRules
{
public:
	static float GetPlayerMovementSpeed() { return _PlayerMovementSpeed; }
	
	//Rocket
	static float GetRocketMovementSpeed() { return _RocketSpeed; }
	static int GetRocketDamage() { return _RocketDamage; }

	//Enemy
	static float GetEnemyMovementSpeed() { return _EnemySpeed; }

	//level
	static float GetLevelMovementSpeed() { return _LevelMovementSpeed; }

private:
	//Spaceship/Player
	static float _PlayerMovementSpeed;

	//Rockets/Missiles
	static float _RocketSpeed;
	static int _RocketDamage;

	//enemy
	static float _EnemySpeed;

	//Level
	static float _LevelMovementSpeed; // this is the vertical movement speed of the whole game (multiply this for paralax)
};