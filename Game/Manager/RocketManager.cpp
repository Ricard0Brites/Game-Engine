#pragma once
#include "RocketManager.h"
#include "..\Missile.h"

RocketManager::RocketManager()
{
}

RocketManager::~RocketManager()
{
}

void RocketManager::DeleteRocket(Missile* RocketToDelete)
{
	dynamic_cast<Actor*>(RocketToDelete)->~Actor();
}
