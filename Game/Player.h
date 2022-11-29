#pragma once
#include "GameEngine.h"


//enum MoveShipX { left = 1, right = 2, noneX = 4 };
//enum MoveShipY { up = 1, down = 2, noneY = 4 };

class Player : public Actor
{
public:


	Player(Actor* Owner);
	~Player();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(InputKeyCodes KeyCode) override;

	virtual void OnKeyReleased(InputKeyCodes KeyCode) override;

	virtual void OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue) override;


protected:
	bool bMoveDirection[4];//0-> up 1->left 2->down 3->right
};