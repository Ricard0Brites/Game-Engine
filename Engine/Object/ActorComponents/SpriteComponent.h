#pragma once
#include "..\..\Data\DataTypes.h"
#include <list>
#include "SDL.h"

class SpriteComponent
{
public:
	SpriteComponent();
	~SpriteComponent();

protected:
	Transform* MyTransform = new Transform;
	std::list<SDL_Texture*> Sprites;
	SDL_Texture* DisplaySprite;

	virtual SDL_Texture* GetSprite(std::string Path);
	virtual std::list<SDL_Texture*> DivideSprite(SDL_Texture* UndividedSprite, Uint8 HorizontalTileAmount, Uint8 VerticalTileAmount);
	virtual void PlayAnimation(bool Loop, float AnimationTotalTime);
	virtual void PlayAnimationReverse(bool Loop, float AnimationTotalTime);
	virtual void StopAnimation();

};

