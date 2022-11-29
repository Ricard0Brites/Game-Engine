#pragma once
#include <iostream>
#include <list>

class Missile;

class RocketManager
{
public:
	RocketManager();
	~RocketManager();

	static void DeleteRocket( Missile* RocketToDelete);

};