#pragma once
#include <iostream>
#include "GameEngine.h"

int main(int argc, char ** argv)
{
    GameEngine engine;
         
    engine.init("Engine", 1280, 720);
    
    //this is a good place to create a game mode/ game instance whatever you wanna call it.
    //this actor should be the one whom controls the game itself... the equivilent of unreal game instance or unity game manager
    
    
    //this is how the character is created and defined
    Actor* Player = engine.CreateActor<Actor>(nullptr);
    engine.SetPlayerReference(Player);
    // ----------------------------------------------

    Actor* TestActor = engine.CreateActor<Actor>(nullptr);
    TestActor->AssignTexture("src/Sprites/drone.bmp", 8, 2, 2);
    TestActor->GetSpriteComponent()->PlayAnimation(true);

    Actor* TestActor2 = engine.CreateActor<Actor>(nullptr);
    TestActor2->AssignTexture("src/Sprites/drone.bmp", 8, 2, 2);
    TestActor2->GetSpriteComponent()->SetLocation(Vector::CreateVector(100, 100, 0), nullptr);
    TestActor2->GetSpriteComponent()->PlayAnimation(true);

    Actor* TestActor3 = engine.CreateActor<Actor>(nullptr);
    TestActor3->AssignTexture("src/Sprites/drone.bmp", 8, 2, 2);
    TestActor3->GetSpriteComponent()->SetLocation(Vector::CreateVector(200, 100, 0), nullptr);
    TestActor3->GetSpriteComponent()->PlayAnimation(true);

    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}