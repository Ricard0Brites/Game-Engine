#pragma once

#include <list>
#include <string>
#include "Data\DataTypes.h"

using namespace std;

struct SDL_Texture;
class Transform;
class Vector;
class Actor;

class SpriteComponent
{
public:
	SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds, Actor* ComponentOwner);
	SpriteComponent();
	~SpriteComponent();

	virtual void Tick(float DeltaSeconds);

	// sets the Sprite Relative location to its parent
	void SetLocation(Vector NewLocation, Actor* Owner);
	void SetScale(Vector NewScale, Actor* Owner);
	//SDL Rect doesn't support Rotation

	//
	Transform* Gettransform() { return MyTransform; }

	//
	virtual void PlayAnimation(bool Loop);
	//plays animation in reverse (X reverse, Y Keeps the order)
	virtual void PlayAnimationReverse(bool Loop);
	//stops animation from playing
	virtual void StopAnimation();

	int GetSpriteWidth() { return fw; }
	int GetSpriteHeight() { return fh; }

protected:
	//
	Transform* MyTransform = nullptr;
	SDL_Texture* DisplaySprite;
	SDL_Rect Quad;

	//Animation
	unsigned int frameCounter = 0;

	bool IsPlayingAnimation = false;
	int tw, th, fw, fh;
	int TextureAmountH, TextureAmountV;
	bool LoopAnimation;
	
	//Animation Timer
	float AnimationTimeInMS, ElapsedTime;
	Actor* Owner;
	SDL_Rect DisplayQuad;

private:
	bool _IsAnimationReverse = false;
};

