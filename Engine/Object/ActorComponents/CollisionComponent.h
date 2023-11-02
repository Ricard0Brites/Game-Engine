#pragma once
#include <list>

class Actor;

class CollisionComponent
{
public:
	virtual void OnCollisionStarted(const Actor* OtherActor) = 0;
	std::list<Actor*> ActorsInRange;
};