#pragma once
#include <iostream>
#include "GameEngine.h"

int main(int argc, char ** argv)
{
    GameEngine engine;
         
    engine.init("Engine", 1280, 720);
    Actor* TestActor = engine.CreateActor<Actor>(nullptr);
    engine.start();
    
    return 0;
}