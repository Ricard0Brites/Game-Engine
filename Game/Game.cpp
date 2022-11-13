// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include "GameEngine.h"

int main(int argc, char ** argv)
{
    GameEngine engine;
         
    engine.init("Engine", 1280, 720);
    engine.start();


    return 0;
}