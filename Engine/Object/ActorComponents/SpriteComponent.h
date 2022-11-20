#pragma once
#include "..\..\Data\DataTypes.h"
#include <list>
#include <string>

struct SDL_Texture;
class Transform;
class Vector;
class Actor;

class SpriteComponent
{
public:
	SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds);
	~SpriteComponent();

	virtual void Tick(float DelataSeconds);

	// sets the Sprite Relative location to its parent
	void SetLocation(Vector NewLocation, Actor* Owner);
	void SetScale(Vector NewScale, Actor* Owner);
	//SDL Rect doesn't support Rotation

	//
	virtual void PlayAnimation(bool Loop);
	//plays animation in reverse (X reverse, Y Keeps the order)
	virtual void PlayAnimationReverse(bool Loop, float AnimationTotalTime);
	//stops animation from playing
	virtual void StopAnimation();

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

	//Loads a surface, makes a texture from it and returns a reference to the texture
	//Don't forget to SDL_DestroyTexture(TextureReference); after you dont need this texture anymore
	virtual SDL_Texture* GetSpriteInLocation(std::string Path);

private:
	bool _IsAnimationReverse = false;

};

