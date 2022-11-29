#pragma once
class GameRules
{
public:
	static float GetPlayerMovementSpeed() { return _MovementSpeed; }
	
	//Rocket
	static float GetRocketMovementSpeed() { return _RocketSpeed; }
	static int GetRocketDamage() { return _RocketDamage; }

private:
	//Spaceship/Player
	static float _MovementSpeed;

	//Rockets/Missiles
	static float _RocketSpeed;
	static int _RocketDamage;

};