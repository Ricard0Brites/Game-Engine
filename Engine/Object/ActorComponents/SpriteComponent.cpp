#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"


SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds)
{
	MyTransform = new Transform;
	MyTransform->IsRelative = true;

	SDL_Surface* surface = GameplayStatics::LoadSurface(TexturePath, GameplayStatics::GetGameEngine()->GetRenderer());
	if(surface) SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
	
	DisplaySprite = SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), surface);
	
	SDL_FreeSurface(surface);

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
	if (IsPlayingAnimation)
	{
	//update animations each frame
#pragma region Dimentions
		SDL_Rect DisplayQuad;

		//TEXTURE POSITION -----------------------------------------------------------
		DisplayQuad.x = (int)MyTransform->GetLocation().X;
		DisplayQuad.y = (int)MyTransform->GetLocation().Y;



		//TEXTURE SCALE --------------------------------------------------------------
		// Quad Scale X = (Texture width / Texture Amount horizontally) * X Scale
		DisplayQuad.w = (int)((float)(tw / TextureAmountH) * MyTransform->GetScale().Y);
		// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
		DisplayQuad.h = (int)((float)(th / TextureAmountV) * MyTransform->GetScale().X);


#pragma endregion

		ElapsedTime += DeltaSeconds;

		if (_IsAnimationReverse)
		{
			//play anim reverse
			if (ElapsedTime >= AnimationTimeInMS / (TextureAmountV * TextureAmountH))
			{
				ElapsedTime = 0;
				Quad.x -= fw;
				if (Quad.x < 0)
				{
					Quad.x = tw - fw;
					
					Quad.y -= fh;
					if (Quad.y > 0) 
					{
						Quad.y = th - fh;
						if (!LoopAnimation) StopAnimation();
					}

				}
			}
		}
		else
		{
			//Animation->Forward
			if (ElapsedTime >= AnimationTimeInMS / (TextureAmountV * TextureAmountH))
			{
				ElapsedTime = 0;
				Quad.x += fw;
				if (Quad.x >= tw) 
				{
					Quad.x = 0;
					Quad.y += fh;
					if (Quad.y >= th) 
					{
						Quad.y = 0;
						if (!LoopAnimation) StopAnimation();
					}
				}
			}
		}

		SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
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

void SpriteComponent::PlayAnimation(bool Loop)
{
	
	_IsAnimationReverse = false;
	IsPlayingAnimation = true;
	LoopAnimation = Loop;
	
}

void SpriteComponent::PlayAnimationReverse(bool Loop)
{
	Quad.x = tw - fw;
	Quad.y = th - fh;
	LoopAnimation = Loop;
	IsPlayingAnimation = true;
	_IsAnimationReverse = true;
}

void SpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
}
