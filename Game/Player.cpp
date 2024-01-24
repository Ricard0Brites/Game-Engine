#include "Player.h"
#include "GameEngine.h"
#include <list>
#include "Missile.h"
#include "GameRules.h"
#include "Components\XennonSpriteComponent.h"
#include <thread>
#include <chrono>
#include "Companion\Companion.h"
#include "Enemies\LonerProjectile.h"
#include "BuffsDebufs\PowerUp.h"
#include "BuffsDebufs\Shield.h"

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
	CreateCompanion();
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
			GameEngine* EngineRef = GameplayStatics::GetGameEngine();
			Validate(EngineRef,);
			Missile* Rocket = EngineRef->CreateActor<Missile>(nullptr);
			Rocket->GetTransform()->SetLocation(Vector::CreateVector(MyTransform->GetLocation().X + (MySprite->GetSpriteWidth() / 2) - 10, MyTransform->GetLocation().Y - (MySprite->GetSpriteHeight() / 2), MyTransform->GetLocation().Z));

			if (Companion1)
			{
				Missile* C1M = EngineRef->CreateActor<Missile>(nullptr);
				C1M->GetTransform()->SetLocation(Vector::CreateVector(
				Companion1->GetTransform()->GetLocation().X + (Companion1->GetSpriteComponent()->GetSpriteWidth() / 2) - 10,
				MyTransform->GetLocation().Y - (Companion1->GetSpriteComponent()->GetSpriteHeight() * 0.7f),
				MyTransform->GetLocation().Z));

			}
			if (Companion2)
			{
				Missile* C2M = EngineRef->CreateActor<Missile>(nullptr);
				C2M->GetTransform()->SetLocation(Vector::CreateVector(
					Companion2->GetTransform()->GetLocation().X + (Companion2->GetSpriteComponent()->GetSpriteWidth() / 2) - 10,
					MyTransform->GetLocation().Y - (Companion2->GetSpriteComponent()->GetSpriteHeight() * 0.7f),
					MyTransform->GetLocation().Z));
			}
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
	if(dynamic_cast<const Companion*>(OtherActor))
		return;
	if(dynamic_cast<const PowerUp*>(OtherActor))
		return;
	if (dynamic_cast<const Shield*>(OtherActor))
		return;
	if(_HasDied)
		return;

	LOG("TAKING DAMAGE", 3);
	_HealthPoints--;
	if(OtherActor)
		const_cast<Actor*>(OtherActor)->CollisionRadius = -1;
		if(OnHealthChangedDelegate)
			OnHealthChangedDelegate();
	
	if(_HealthPoints != 0)
		return;
	//kill player
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

void Player::CreateCompanion()
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );
	if (!Companion1)
	{
		Companion1 = EngineRef->CreateActor<Companion>(this);
		Companion1->GetTransform()->IsRelative = true;
		Companion1->GetTransform()->SetRelativeLocation(Vector::CreateVector(MySprite->GetSpriteWidth() * 1.1f, MySprite->GetSpriteHeight() * -0.1f, 0));
	}
	else if(!Companion2)
	{
		Companion2 = EngineRef->CreateActor<Companion>(this);
		Companion2->GetTransform()->IsRelative = true;
		Companion2->GetTransform()->SetRelativeLocation(Vector::CreateVector(MySprite->GetSpriteWidth() *  -0.6f, MySprite->GetSpriteHeight() * -0.1f, 0));
	}
}

void Player::DestroyCompanion()
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );
	if (Companion2)
	{
		EngineRef->RemoveActor(Companion2);
		Companion2 = nullptr;
	}
	else if (Companion1)
	{
		EngineRef->RemoveActor(Companion1);
		Companion1 = nullptr;
	}
}

void Player::DestroyCompanion(Companion* Ref)
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef, );

	if (Ref == Companion1)
	{
		EngineRef->RemoveActor(Companion1);
		Companion1 = nullptr;
	}
	else if (Ref == Companion2)
	{
		EngineRef->RemoveActor(Companion2);
		Companion2 = nullptr;
	}
}
