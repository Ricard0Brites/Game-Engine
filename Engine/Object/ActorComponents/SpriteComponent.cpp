#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"


SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY)
{
	MyTransform = new Transform;
	MyTransform->IsRelative = true;

	DisplaySprite = GameplayStatics::LoadTexture(TexturePath, GameplayStatics::GetGameEngine()->GetRenderer());
	SDL_QueryTexture(DisplaySprite, NULL, NULL, &tw, &th);

	TextureAmountH = TilesX;
	TextureAmountV = TilesY;

	fw = tw / TextureAmountH;
	fh = th / TextureAmountV;

	Quad.x = 0; Quad.y = 0;
	Quad.w = fw; Quad.h = fh;
}

SpriteComponent::~SpriteComponent()
{
	delete MyTransform;
}

void SpriteComponent::Tick(float DelataSeconds)
{
	SDL_Rect DisplayQuad;
	
	//TEXTURE POSITION -----------------------------------------------------------
	DisplayQuad.x = 0;
	DisplayQuad.y = 0;
	


	//TEXTURE SCALE --------------------------------------------------------------
	// Quad Scale X = (Texture width / Texture Amount horizontally) * X Scale
	DisplayQuad.w = (int)((float)(tw/TextureAmountH) * MyTransform->GetRelativeScale().Y);
	// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
	DisplayQuad.h = (int)((float)(th/TextureAmountV) * MyTransform->GetRelativeScale().X);


	if (true)//IsPlayingAnimation)
	{
		if (_IsAnimationReverse)
		{
			//play anim reverse
		}
		else
		{
			//not reversed animation

			frameCounter++;

			if (frameCounter >= 60)
			{
				frameCounter = 0;

				Quad.x += fw;
				if (Quad.x >= tw) Quad.x = 0;
				if (Quad.y >= th) Quad.y = 0;
			}
		}
		SDL_RenderClear(GameplayStatics::GetGameEngine()->GetRenderer());
		SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
		SDL_RenderPresent(GameplayStatics::GetGameEngine()->GetRenderer());
	}
}

SDL_Texture* SpriteComponent::GetSpriteInLocation(std::string Path)
{	
	return SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), SDL_LoadBMP(&(Path)[0]));	
}

void SpriteComponent::PlayAnimation(bool Loop)
{
	_IsAnimationReverse = false;
	IsPlayingAnimation = true;
	
}

void SpriteComponent::PlayAnimationReverse(bool Loop, float AnimationTotalTime)
{
	IsPlayingAnimation = true;
	_IsAnimationReverse = true;
}

void SpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
	OnAnimationComplete();
}

void SpriteComponent::OnAnimationComplete()
{

}
