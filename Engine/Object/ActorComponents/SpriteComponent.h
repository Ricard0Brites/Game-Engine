#pragma once
#include "..\..\Data\DataTypes.h"
#include <list>
#include <string>

struct SDL_Texture;
class Transform;

class SpriteComponent
{
public:
	SpriteComponent(std::string TexturePath, int TilesX, int TilesY);
	~SpriteComponent();

	virtual void Tick(float DelataSeconds);

protected:
	Transform* MyTransform;
	SDL_Texture* DisplaySprite;
	SDL_Rect Quad;
	unsigned int frameCounter = 0;
	bool IsPlayingAnimation = false;
	int tw, th, fw, fh;
	int TextureAmountH, TextureAmountV;

	//Loads a surface, makes a texture from it and returns a reference to the texture
	//Don't forget to SDL_DestroyTexture(TextureReference); after you dont need this texture anymore
	virtual SDL_Texture* GetSpriteInLocation(std::string Path);
	virtual void PlayAnimation(bool Loop);
	virtual void PlayAnimationReverse(bool Loop, float AnimationTotalTime);
	virtual void StopAnimation();
	virtual void OnAnimationComplete();

private:
	bool _IsAnimationReverse = false;

};

