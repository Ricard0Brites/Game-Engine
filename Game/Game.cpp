#pragma once
#include <iostream>
#include "GameEngine.h"

#include "Systems/Spawner.h"
#include "GameRules.h"

#include "Player.h"
#include "Enemies/Loner.h"
#include "Enemies/Asteroid.h"
#include "Enemies/Rusher.h"
#include "Enemies/Drone.h"
#include "Companion\Companion.h"

int main(int argc, char** argv)
{
    GameEngine engine;
    int windowWidth = 0, windowHeight = 0;
    GameRules::GetWindowDimentions(windowWidth, windowHeight);

    engine.init("Game", windowWidth, windowHeight);
    
    //World(Background)
	Actor* BgActor = engine.CreateActor<Actor>(nullptr);
	BgActor->AssignTexture("src/Sprites/galaxy2.bmp", 1, 1, 1, BgActor);
    BgActor->GetTransform()->SetScale(Vector::CreateVector(2, 2, 0));
	BgActor->GetSpriteComponent()->PlayAnimation(true);
    BgActor->CollisionRadius = -1;

    //Player
    //this is how the character is created and defined
    Player* Player1 = engine.CreateActor<Player>(nullptr);
	Player1->GetTransform()->SetLocation(Vector::CreateVector(500, 600, 0));
    Player1->GetCustomSpriteComponent()->PlayAnimation(true);
    engine.SetPlayerReference(Player1);

    //Enemies
    Spawner spawner;
    spawner.InitSpawner();

    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}


