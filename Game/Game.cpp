#pragma once
#include <iostream>
#include "GameEngine.h"

#include "Player.h"
#include "Enemies/Loner.h"
#include "Systems/Spawner.h"
#include "Enemies/Asteroid.h"
#include "GameRules.h"
#include "Enemies/Rusher.h"

#if _DEBUG
    #define CLASSTOTEST Rusher
    #define DEBUGENTITYNUM 1
#endif

int main(int argc, char** argv)
{
    GameEngine engine;
    int windowWidth = 0, windowHeight = 0;
    GameRules::GetWindowDimentions(windowWidth, windowHeight);

    engine.init("Engine", windowWidth, windowHeight);
  

    //this is a good place to create a game mode/ game instance whatever you wanna call it.
    //this actor should be the one whom controls the game itself... the equivalent of unreal game instance or unity game manager
    
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
#if _DEBUG
    CLASSTOTEST* enemy[DEBUGENTITYNUM + 1] = {};

    for (int i = 0; i < DEBUGENTITYNUM + 1; ++i)
    {
        enemy[i] = engine.CreateActor<CLASSTOTEST>(nullptr);
		enemy[i]->GetTransform()->SetLocation(Vector::CreateVector((float)(windowWidth / (DEBUGENTITYNUM + 1)) * (float)(i + 1), (float)windowHeight / 4, 0));
    }
#endif
#if _RELEASE
    Spawner spawner;
    spawner.InitSpawner();
#endif
    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}


