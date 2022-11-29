#include "Player.h"
#include "GameEngine.h"
#include <list>

#include "Missile.h"
#include "GameRules.h"




Player::Player(Actor* Parent) : Actor(Parent)
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
}

void Player::Tick(float DeltaSeconds)
{
	if (MySprite) MySprite->Tick(DeltaSeconds);
	
	if (bMoveDirection[0])//up
		GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(0, -0.2f, 0)) * DeltaSeconds);
	
	if (bMoveDirection[1])//left
		GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(-0.2f, 0, 0)) * DeltaSeconds);
	
	if (bMoveDirection[2])//down
		GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(0, 0.2f, 0)) * DeltaSeconds);
	
	if (bMoveDirection[3])//right
		GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(0.2f, 0, 0)) * DeltaSeconds);

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
			Missile* Rocket = GameplayStatics::GetGameEngine()->CreateActor<Missile>(nullptr);
			Rocket->GetTransform()->SetLocation(Vector::CreateVector(MyTransform->GetLocation().X + (MySprite->GetSpriteWidth() / 2) - 10, MyTransform->GetLocation().Y - (MySprite->GetSpriteHeight() / 2), MyTransform->GetLocation().Z));
			Rocket->AssignTexture("src/Sprites/missile1.bmp", 2, 1, 0.5f, Rocket);
			Rocket->GetSpriteComponent()->SetScale(Vector::CreateVector(1,1,1), nullptr);
			Rocket->GetSpriteComponent()->PlayAnimation(true);
			Rocket->StartMovement();
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
	GetTransform()->SetLocation(GetTransform()->GetLocation() += (AxisValue * 0.2f) * GameplayStatics::GetGameEngine()->GetDeltaSeconds());
}



