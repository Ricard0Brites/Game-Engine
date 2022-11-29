#pragma once
#include <iostream>
#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"

int main(int argc, char ** argv)
{
    GameEngine engine;
	const int TotalEnemies = 10;
	float posX = 0;
         
    engine.init("Engine", 1280, 720);
  

    //this is a good place to create a game mode/ game instance whatever you wanna call it.
    //this actor should be the one whom controls the game itself... the equivalent of unreal game instance or unity game manager
    
    //World(Background)
	Actor* BgActor = engine.CreateActor<Actor>(nullptr);
	BgActor->AssignTexture("src/Sprites/galaxy2.bmp", 1, 1, 1, BgActor);
    BgActor->GetSpriteComponent()->SetScale(Vector::CreateVector(2, 2, 0), nullptr);
	BgActor->GetSpriteComponent()->PlayAnimation(true);

    //Player
    //this is how the character is created and defined
    Player* Player1 = engine.CreateActor<Player>(nullptr);
	Player1->AssignTexture("src/Sprites/ship1.bmp", 7, 1, 1, Player1);
	Player1->GetSpriteComponent()->SetLocation(Vector::CreateVector(500, 600, 0), nullptr);
	Player1->GetSpriteComponent()->PlayAnimation(true);
    engine.SetPlayerReference(Player1);

    //Enemies
    Enemy* enemy[TotalEnemies]{};

    for (int i = 0; i < 10; i++) 
    {
        enemy[i] = engine.CreateActor<Enemy>(nullptr);
		enemy[i]->AssignTexture("src/Sprites/LonerB.bmp", 4, 4, 2, enemy[i]);
		enemy[i]->GetSpriteComponent()->SetLocation(Vector::CreateVector(posX += 100, 0, 0), nullptr);
		enemy[i]->GetSpriteComponent()->PlayAnimation(true);
    }

   
  
    


    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}


