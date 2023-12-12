#pragma once
#include <iostream>
#include "GameEngine.h"
#include "Player.h"
#include "Enemies/Loner.h"
#include "Spawner.h"

#if _DEBUG
    #define CLASSTOTEST Loner
#endif
int main(int argc, char** argv)
{
    GameEngine engine;
	const int TotalEnemies = 5;
         
    engine.init("Engine", 1280, 720);
  

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
    CLASSTOTEST* enemy[TotalEnemies]{};

    for (int i = 0; i < TotalEnemies; ++i)
    {
        enemy[i] = engine.CreateActor<CLASSTOTEST>(nullptr);
		enemy[i]->AssignTexture("src/Sprites/LonerB.bmp", 4, 4, 2, (Actor*)enemy[i]);
		enemy[i]->GetTransform()->SetLocation(Vector::CreateVector((150 * (float)i) + 100, 0, 0));
		enemy[i]->GetSpriteComponent()->PlayAnimation(true);
    }

    Spawner spawner;
#endif
#if _RELEASE
    spawner.InitSpawner();
#endif
    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}


