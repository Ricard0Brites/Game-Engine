#include "Asteroid.h"
#define GETTEXPATH(TextureName) "src/Sprites/" #TextureName

Asteroid::Asteroid(Actor* Parent) : Actor(Parent)
{
	Asteroids[0].Path = GETTEXPATH(GAster32.bmp);
	Asteroids[0].TileX = 8;
	Asteroids[0].TileY = 2;

	Asteroids[1].Path = GETTEXPATH(GAster64.bmp);
	Asteroids[1].TileX = 8;
	Asteroids[1].TileY = 3;


	Asteroids[2].Path = GETTEXPATH(GAster96.bmp);
	Asteroids[2].TileX = 5;
	Asteroids[2].TileY = 5;


	Asteroids[3].Path = GETTEXPATH(MAster32.bmp);
	Asteroids[3].TileX = 8;
	Asteroids[3].TileY = 2;


	Asteroids[4].Path = GETTEXPATH(MAster64.bmp);
	Asteroids[4].TileX = 8;
	Asteroids[4].TileY = 3;


	Asteroids[5].Path = GETTEXPATH(MAster96.bmp);
	Asteroids[5].TileX = 5;
	Asteroids[5].TileY = 5;


	Asteroids[6].Path = GETTEXPATH(SAster32.bmp);
	Asteroids[6].TileX = 8;
	Asteroids[6].TileY = 2;


	Asteroids[7].Path = GETTEXPATH(SAster64.bmp);
	Asteroids[7].TileX = 8;
	Asteroids[7].TileY = 3;


	Asteroids[8].Path = GETTEXPATH(SAster96.bmp);
	Asteroids[8].TileX = 5;
	Asteroids[8].TileY = 5;

	for(AnimationParameters& AnimParams : Asteroids)
	{
		AnimParams.AnimationTime = AnimParams.TileX * AnimParams.TileY * 0.0625f;
	}
}

void Asteroid::BeginPlay()
{
	int RNG = (rand() % 10);
	AssignTexture(Asteroids[RNG].Path, Asteroids[RNG].TileX, Asteroids[RNG].TileY, Asteroids[RNG].AnimationTime, this);
	MySprite->PlayAnimation(true);
}

void Asteroid::OnCollisionStarted(const Actor* OtherActor)
{
	
}
