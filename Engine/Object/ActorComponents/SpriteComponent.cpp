#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"


SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds)
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

	AnimationTimeInMS = AnimationTimeInSeconds * 1000;
	ElapsedTime = 0;
}

SpriteComponent::~SpriteComponent()
{
	delete MyTransform;
}

void SpriteComponent::Tick(float DeltaSeconds)
{
	SDL_Rect DisplayQuad;
	
	//TEXTURE POSITION -----------------------------------------------------------
	DisplayQuad.x = (int)MyTransform->GetRelativeLocation().X;
	DisplayQuad.y = (int)MyTransform->GetRelativeLocation().Y;
	


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

			/*frameCounter++;

			if (frameCounter >= 60)
			{
				EXECUTIONLOG;
				frameCounter = 0;
				Quad.x += fw;
				if (Quad.x >= tw) Quad.x = 0;
				if (Quad.y >= th) Quad.y = 0;
			}*/
			ElapsedTime += DeltaSeconds;

			if (ElapsedTime >= AnimationTimeInMS / (TextureAmountV * TextureAmountH))
			{
				ElapsedTime = 0;
				Quad.x += fw;
				if (Quad.x >= tw) 
				{
					Quad.x = 0;
					Quad.y += fh;
					if (Quad.y >= th) Quad.y = 0;
				}
			}
		}
		SDL_RenderClear(GameplayStatics::GetGameEngine()->GetRenderer());
		SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
		SDL_RenderPresent(GameplayStatics::GetGameEngine()->GetRenderer());
	}
}

void SpriteComponent::SetLocation(Vector NewLocation, Actor* Owner)
{
	if (!Owner) 
	{
		MyTransform->SetLocation(NewLocation);
	}
	else
	{
		Vector* FinalVector = new Vector;
		FinalVector->Zero(true);

		// gets the absolute owner
		while (Owner->GetOwner())
		{
			*FinalVector += Owner->GetTransform()->GetLocation();
			Owner = Owner->GetOwner();
		}
		//adds all of the parent locations
		MyTransform->SetLocation(NewLocation + Owner->GetTransform()->GetLocation() + *FinalVector);
	}
}

void SpriteComponent::SetScale(Vector NewScale, Actor* Owner)
{
	if (!Owner)
	{
		MyTransform->SetScale(NewScale);
	}
	else
	{
		Vector* TempScale = new Vector;
		TempScale->Zero(true);

		while (Owner->GetOwner())
		{
			*TempScale *= Owner->GetTransform()->GetScale();
			Owner = Owner->GetOwner();
		}

		MyTransform->SetScale(NewScale * (*TempScale) * Owner->GetTransform()->GetScale());
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
