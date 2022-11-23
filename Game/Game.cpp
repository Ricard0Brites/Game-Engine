#pragma once
#include <iostream>
#include "GameEngine.h"

int main(int argc, char ** argv)
{
    GameEngine engine;
         
    engine.init("Engine", 1280, 720);
    
    //this is a good place to create a game mode/ game instance whatever you wanna call it.
    //this actor should be the one whom controls the game itself... the equivilent of unreal game instance or unity game manager
    
    
    
    Actor* TestActor = engine.CreateActor<Actor>(nullptr);
    TestActor->AssignTexture("F:/Year3/Game-Engine/Engine/Temp/graphics/drone.bmp", 8, 2, 2);
    TestActor->GetSpriteComponent()->PlayAnimation(true);



    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}