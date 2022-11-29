#include "Player.h"
#include "GameEngine.h"
#include <list>




Player::Player(Actor* Parent) : Actor(Parent)
{
	Owner = Parent;
	MyTransform = new Transform();
}

Player::~Player()
{
	if (MyTransform) delete MyTransform;
	if (MySprite) delete MySprite;
}

void Player::BeginPlay()
{
	playerActor = GameplayStatics::GetGameEngine()->GetPlayer();
}

void Player::Tick(float DeltaSeconds)
{
	if (MySprite) MySprite->Tick(DeltaSeconds);
	
	if (bMoveDirection[0])//up
		playerActor->GetTransform()->SetLocation(playerActor->GetTransform()->GetLocation() += (Vector::CreateVector(0, -0.2f, 0)) * DeltaSeconds);
	
	if (bMoveDirection[1])//left
		playerActor->GetTransform()->SetLocation(playerActor->GetTransform()->GetLocation() += (Vector::CreateVector(-0.2f, 0, 0)) * DeltaSeconds);
	
	if (bMoveDirection[2])//down
		playerActor->GetTransform()->SetLocation(playerActor->GetTransform()->GetLocation() += (Vector::CreateVector(0, 0.2f, 0)) * DeltaSeconds);
	
	if (bMoveDirection[3])//right
		playerActor->GetTransform()->SetLocation(playerActor->GetTransform()->GetLocation() += (Vector::CreateVector(0.2f, 0, 0)) * DeltaSeconds);

}

void Player::OnKeyPressed(InputKeyCodes KeyCode)
{
	

	switch (KeyCode)
	{
		case InputKeyCodes::K_w:
		case InputKeyCodes::K_Up:
		case InputKeyCodes::GamepadArrowTop:
		{
			bMoveDirection[0] = true;
			break;
		}
		case InputKeyCodes::K_a:
		case InputKeyCodes::K_Left:
		case InputKeyCodes::GamepadArrowLeft:
		{
			bMoveDirection[1] = true;
			break;
		}
		case InputKeyCodes::K_s:
		case InputKeyCodes::K_Down:
		case InputKeyCodes::GamepadArrowBottom:
		{
			bMoveDirection[2] = true;
			break;
		}
		case InputKeyCodes::K_d:
		case InputKeyCodes::K_Right:
		case InputKeyCodes::GamepadArrowRight:
		{
			bMoveDirection[3] = true;
			break;
		}
		case InputKeyCodes::K_Space:
		case InputKeyCodes::GamepadFaceBottom:
		{
			LOG("Missile Shot", 1);
			break;
		}


	}

	
}

void Player::OnKeyReleased(InputKeyCodes KeyCode)
{
	switch (KeyCode)
	{
		case InputKeyCodes::K_w:
		case InputKeyCodes::K_Up:
		case InputKeyCodes::GamepadArrowTop:
		{
			bMoveDirection[0] = false;
			break;
		}
		case InputKeyCodes::K_a:
		case InputKeyCodes::K_Left:
		case InputKeyCodes::GamepadArrowLeft:
		{
			bMoveDirection[1] = false;
			break;
		}
		case InputKeyCodes::K_s:
		case InputKeyCodes::K_Down:
		case InputKeyCodes::GamepadArrowBottom:
		{
			bMoveDirection[2] = false;
			break;
		}
		case InputKeyCodes::K_d:
		case InputKeyCodes::K_Right:
		case InputKeyCodes::GamepadArrowRight:
		{
			bMoveDirection[3] = false;
			break;
		}

	}
}

void Player::OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue)
{
	playerActor->GetTransform()->SetLocation(playerActor->GetTransform()->GetLocation() += (AxisValue * 0.2f) * GameplayStatics::GetGameEngine()->GetDeltaSeconds());
}



