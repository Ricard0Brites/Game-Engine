#include "Player.h"
#include "../GameEngine.h"
#include <list>




Player::Player(Actor* Parent):Actor(Parent)
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

	//Vector initialLocation = playerActor->GetSpriteComponent()->Gettransform()->GetLocation();

	//"sometimes simple is better"
	
	if (bMoveDirection[0])//up
		playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0, -0.2f, 0)) * DeltaSeconds, nullptr);
	
	if (bMoveDirection[1])//left
		playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(-0.2f, 0, 0)) * DeltaSeconds, nullptr);
	
	if (bMoveDirection[2])//down
		playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0, 0.2f, 0)) * DeltaSeconds, nullptr);
	
	if (bMoveDirection[3])//right
		playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0.2f, 0, 0)) * DeltaSeconds, nullptr);



	//switch (_moveShipX)
	//{
	//case left:

	//	playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(-0.2f, 0, 0)) * DeltaSeconds, nullptr);

	//	break;
	//case right:

	//	playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0.2f, 0, 0)) * DeltaSeconds, nullptr);

	//	break;

	//}


	//switch (_moveShipY)
	//{
	//case up:

	//	playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0, -0.2f, 0)) * DeltaSeconds, nullptr);

	//	break;

	//case down:

	//	playerActor->GetSpriteComponent()->SetLocation(playerActor->GetSpriteComponent()->Gettransform()->GetLocation() += (Vector::CreateVector(0, 0.2f, 0)) * DeltaSeconds, nullptr);

	//	break;


	//}



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
			//_moveShipY = MoveShipY::up;


			break;
		}
		case InputKeyCodes::K_a:
			case InputKeyCodes::K_Left:
				case InputKeyCodes::GamepadArrowLeft:
		{
			bMoveDirection[1] = true;
			//_moveShipX = MoveShipX::left;


			break;
		}
		case InputKeyCodes::K_s:
			case InputKeyCodes::K_Down:
				case InputKeyCodes::GamepadArrowBottom:
		{
			bMoveDirection[2] = true;
			//_moveShipY = MoveShipY::down;


			break;
		}
		case InputKeyCodes::K_d:
			case InputKeyCodes::K_Right:
				case InputKeyCodes::GamepadArrowRight:
		{
			bMoveDirection[3] = true;
			//_moveShipX = MoveShipX::right;


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
		//	_moveShipY = MoveShipY::noneY;


			break;
		}
		case InputKeyCodes::K_a:
			case InputKeyCodes::K_Left:
				case InputKeyCodes::GamepadArrowLeft:
		{
			bMoveDirection[1] = false;
			//_moveShipX = MoveShipX::noneX;


			break;
		}
		case InputKeyCodes::K_s:
			case InputKeyCodes::K_Down:
				case InputKeyCodes::GamepadArrowBottom:
		{
			bMoveDirection[2] = false;
			//_moveShipY = MoveShipY::noneY;


			break;
		}
		case InputKeyCodes::K_d:
			case InputKeyCodes::K_Right:
				case InputKeyCodes::GamepadArrowRight:
		{
			bMoveDirection[3] = false;
			//_moveShipX = MoveShipX::noneX;


			break;
		}

	}
}

void Player::OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue)
{

}



