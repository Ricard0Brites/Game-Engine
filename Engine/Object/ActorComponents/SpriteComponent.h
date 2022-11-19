#pragma once
#include "..\..\Data\DataTypes.h"
#include <list>
#include <string>

struct SDL_Texture;
class Transform;

class SpriteComponent
{
public:
	SpriteComponent();
	~SpriteComponent();

protected:
	Transform* MyTransform;
	SDL_Texture* DisplaySprite;

	bool IsPlayingAnimation = false;

	//Loads a surface, makes a texture from it and returns a reference to the texture
	//Don't forget to SDL_DestroyTexture(TextureReference); after you dont need this texture anymore
	virtual SDL_Texture* GetSpriteInLocation(std::string Path);
	virtual void PlayAnimation(bool Loop, float AnimationTotalTime, void (&OnCompleted)());
	virtual void PlayAnimationReverse(bool Loop, float AnimationTotalTime);
	virtual void StopAnimation();
	virtual void OnAnimationComplete();

public:
	virtual void Tick(float DelataSeconds);
};

