#include "Player.h"
#include "GameEngine.h"
#include <list>

#include "Missile.h"
#include "GameRules.h"

#include "Components\XennonSpriteComponent.h"

#include <thread>
#include <chrono>

#define PLAYERSPEED 0.2f

Player::Player(Actor* Parent) : Actor(Parent)
{
	MySprite = (SpriteComponent*) new XennonStaticSpriteComponent("src/Sprites/Ship1.bmp", 7, 1, this, _IdleShipAnimIndex); // starting state = 4
	CollisionRadius = max((float)MySprite->GetSpriteWidth(), (float)MySprite->GetSpriteHeight()) * 0.5f;
	IsLevelActor = false;
}

Player::~Player()
{
	if(MySprite) 
	{
		delete MySprite; 
		MySprite = nullptr;
	}
}

void Player::BeginPlay()
{
	_HealthPoints *= 2;
}

void Player::Tick(float DeltaSeconds)
{
	if(!MySprite) return;
	if(!MyTransform) return;
	if(IsPendingKill) return;

	if (MySprite)MySprite->Tick(DeltaSeconds);
	
	if (bMoveDirection[0])//up
	{
		if (GetTransform()->GetLocation().Y >= 0 - (GetCustomSpriteComponent()->GetTextureHeight() / 2))
		{
			GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(0, -PLAYERSPEED, 0)) * DeltaSeconds);
		}
	}

	if (bMoveDirection[1])//left
	{
		if (GetTransform()->GetLocation().X >= 0 - (GetCustomSpriteComponent()->GetTextureWidth() / 2))
		{
			GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(-PLAYERSPEED, 0, 0)) * DeltaSeconds);
		}
	}

	if (bMoveDirection[2])//down
	{
		if (GetTransform()->GetLocation().Y <= GameplayStatics::GetScreenHeight() - (GetCustomSpriteComponent()->GetTextureHeight() / 2))
		{
			GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(0, PLAYERSPEED, 0)) * DeltaSeconds);
		}
	}

	if (bMoveDirection[3])//right
	{
		if (GetTransform()->GetLocation().X <= GameplayStatics::GetScreenWidth() - (GetCustomSpriteComponent()->GetTextureWidth() / 2))
		{
			GetTransform()->SetLocation(GetTransform()->GetLocation() += (Vector::CreateVector(PLAYERSPEED, 0, 0)) * DeltaSeconds);
		}
	}
		
	if (_CanKeepShooting)
	{	
		if( _ShootingTimer >= GameRules::GetTimeBetweenShots())
		{
			Missile* Rocket = GameplayStatics::GetGameEngine()->CreateActor<Missile>(nullptr);
			Rocket->GetTransform()->SetLocation(Vector::CreateVector(MyTransform->GetLocation().X + (MySprite->GetSpriteWidth() / 2) - 10, MyTransform->GetLocation().Y - (MySprite->GetSpriteHeight() / 2), MyTransform->GetLocation().Z));
			_ShootingTimer = 0;
		}
	}
	_ShootingTimer += DeltaSeconds;
	// the players falling speed (AKA Level Movement)
	if (GetTransform()->GetLocation().Y <= GameplayStatics::GetScreenHeight() - (GetCustomSpriteComponent()->GetTextureHeight() / 2) && !bMoveDirection[0])
	{
		GetTransform()->SetLocation(Vector::CreateVector(
		/*X*/ GetTransform()->GetLocation().X,
		/*Y*/ GetTransform()->GetLocation().Y + GameRules::GetLevelMovementSpeed(),
		/*Z*/ 0
	));
	}
	
}

void Player::OnKeyPressed(InputKeyCodes KeyCode)
{
	if(IsPendingKill) return;
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

			if(!_AnimStateManager) GetCustomSpriteComponent()->AnimTansitionToIndex(0, 0.1f, &_AnimStateManager);
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
			if(!_AnimStateManager) GetCustomSpriteComponent()->AnimTansitionToIndex(7, 0.1f, &_AnimStateManager);
			break;
		}
		case InputKeyCodes::K_Space:
		case InputKeyCodes::GamepadFaceBottom:
		{	
			_CanKeepShooting = true; 
			break;
		}
	}
}

void Player::OnKeyReleased(InputKeyCodes KeyCode)
{
	if(IsPendingKill) return;
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
			if(!_AnimStateManager) GetCustomSpriteComponent()->AnimTansitionToIndex(_IdleShipAnimIndex, 0.1f, &_AnimStateManager);
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
			if(!_AnimStateManager) GetCustomSpriteComponent()->AnimTansitionToIndex(_IdleShipAnimIndex, 0.1f, &_AnimStateManager);
			break;
		}
		case InputKeyCodes::K_Space:
		case InputKeyCodes::GamepadFaceBottom:
		{
			_CanKeepShooting = false;
		}
	}
}

void Player::OnInputAxis(InputKeyCodes KeyCode, Vector AxisValue)
{
	if(GetTransform())
		GetTransform()->SetLocation(GetTransform()->GetLocation() += (AxisValue * 0.2f) * GameplayStatics::GetGameEngine()->GetDeltaSeconds());
}

void Player::OnCollisionStarted(const Actor* OtherActor)
{
	if(dynamic_cast<const Missile*>(OtherActor))
		return;
	if(_HasDied)
		return;
	LOG("TAKING DAMAGE", 3);
	_HealthPoints--;
	const_cast<Actor*>(OtherActor)->CollisionRadius = -1;
	if(_HealthPoints != 0)
		return;

	_HasDied = true;
	delete MySprite;
	MySprite = nullptr;
	MySprite = new SpriteComponent("src/Sprites/Ship2.bmp", 7, 3, 2, this);
	MySprite->PlayAnimation(false);
	CollisionRadius = -1;

	// destroy actor (ideally this would be done with delegates but making a delegate system 
	//would take too much time)
	std::thread([&]() 
	{
		GameplayStatics::Delay(3);
		DestroyPlayer();
	}).detach();
}

void Player::DestroyPlayer()
{
	GameplayStatics::GetGameEngine()->RemoveActor(this);
}