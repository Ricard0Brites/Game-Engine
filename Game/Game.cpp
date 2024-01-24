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
#include "UserInterface/Widget.h"

GameEngine engine;
Player* Player1 = nullptr;
Widget* UI = nullptr;

void UpdateUI()
{
    UI->SetText("Health " + std::to_string(Player1->GetHP()));
};
int main(int argc, char** argv)
{
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
    Player1 = engine.CreateActor<Player>(nullptr);
	Player1->GetTransform()->SetLocation(Vector::CreateVector(500, 600, 0));
    Player1->GetCustomSpriteComponent()->PlayAnimation(true);
    engine.SetPlayerReference(Player1);

    //UI
        //Player HP Bottom Left
    UI = engine.CreateActor<Widget>(nullptr);
    UI->GetTransform()->SetLocation(Vector::CreateVector(0, 0, 0));
    UI->Alignment.SetAlignment(WidgetAnchorH::Left, WidgetAnchorV::Bottom);
    UI->SetText("Health " + std::to_string(Player1->GetHP())); // the space generates a null surface error... this is safe.
    
    
    Player1->OnHealthChangedDelegate = &UpdateUI;
    //Enemies
    Spawner spawner;
    spawner.InitSpawner();

    engine.start();// no code after this function will be called. from this point on to do anything it has to be inside the gameloop... this means only spawned and active actors can spawn other actors.
    
    return 0;
}


