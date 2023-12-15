#include "Asteroid.h"
#include "..\Missile.h"
#include "..\GameRules.h"
#define GETTEXPATH(TextureName) "src/Sprites/" #TextureName

Asteroid::Asteroid(Actor* Parent) : Actor(Parent)
{
	switch(AsteroidType)
	{
		case 0:
			Asteroids[2].Path = GETTEXPATH(GAster32.bmp);
			Asteroids[2].TileX = 8;
			Asteroids[2].TileY = 2;

			Asteroids[1].Path = GETTEXPATH(GAster64.bmp);
			Asteroids[1].TileX = 8;
			Asteroids[1].TileY = 3;

			Asteroids[0].Path = GETTEXPATH(GAster96.bmp);
			Asteroids[0].TileX = 5;
			Asteroids[0].TileY = 5;
			break;

		case 1:
			Asteroids[2].Path = GETTEXPATH(SAster32.bmp);
			Asteroids[2].TileX = 8;
			Asteroids[2].TileY = 2;

			Asteroids[1].Path = GETTEXPATH(SAster64.bmp);
			Asteroids[1].TileX = 8;
			Asteroids[1].TileY = 3;

			Asteroids[0].Path = GETTEXPATH(SAster96.bmp);
			Asteroids[0].TileX = 5;
			Asteroids[0].TileY = 5;
			break;

		case 2:
			Asteroids[2].Path = GETTEXPATH(MAster32.bmp);
			Asteroids[2].TileX = 8;
			Asteroids[2].TileY = 2;

			Asteroids[1].Path = GETTEXPATH(MAster64.bmp);
			Asteroids[1].TileX = 8;
			Asteroids[1].TileY = 3;

			Asteroids[0].Path = GETTEXPATH(MAster96.bmp);
			Asteroids[0].TileX = 5;
			Asteroids[0].TileY = 5;
			break;
		default:
			break;
	}

	for(AnimationParameters& AnimParams : Asteroids)
	{
		AnimParams.AnimationTime = AnimParams.TileX * AnimParams.TileY * 0.0625f;
	}
}

void Asteroid::BeginPlay()
{
	AssignTexture(Asteroids[AsteroidState].Path, Asteroids[AsteroidState].TileX, Asteroids[AsteroidState].TileY, Asteroids[AsteroidState].AnimationTime, this);
	MySprite->PlayAnimation(true);
	
	if (AsteroidType == 2)
		IsInvincible = true;
}

void Asteroid::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);
	GetTransform()->SetLocation(((FallingDirection * GameRules::GetAsteroidFallingSpeed())) * DeltaSeconds + GetTransform()->GetLocation());
}

void Asteroid::OnCollisionStarted(const Actor* OtherActor)
{
	if(dynamic_cast<const Missile*>(OtherActor) && !IsInvincible)
	{
		GameEngine* EngineRef = GameplayStatics::GetGameEngine();
		Validate(EngineRef, );
		//1 hit
		if (AsteroidType == 0)
		{
			AsteroidState++;
			if(AsteroidState < (sizeof(Asteroids) / sizeof(Asteroids[0])))
			{
				SpawnChildAsteroids();
				EngineRef->RemoveActor(this);
				return;
			}
			EngineRef->RemoveActor(this);
		}
		// 2 hit
		else if (AsteroidType == 1)
		{
			TypeTwoAsteroidHitCount++;
			if (TypeTwoAsteroidHitCount >= 2)
			{
				AsteroidState++;
				TypeTwoAsteroidHitCount = 0;
				if (AsteroidState < (sizeof(Asteroids) / sizeof(Asteroids[0])))
				{
					SpawnChildAsteroids();
					EngineRef->RemoveActor(this);
					return;
				}
				EngineRef->RemoveActor(this);
			}
		}
	}
}

void Asteroid::SpawnChildAsteroids()
{
	GameEngine* EngineRef = GameplayStatics::GetGameEngine();
	Validate(EngineRef,);
	for (int i = 0; i < 3; ++i)
	{
		Asteroid *ActorRef = EngineRef->CreateActor<Asteroid>(nullptr);
		ActorRef->GetTransform()->SetLocation(GetTransform()->GetLocation());
		ActorRef->SetAsteroidType(AsteroidType);
		ActorRef->SetAsteroidState(AsteroidState);
		ActorRef->SetMovementDirection(Vector::CreateVector(-0.5f + (i * 0.5f), 1, 0));
	}
}
