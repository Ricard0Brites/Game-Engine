#pragma once
#include "XennonSpriteComponent.h"

#include <thread>
#include <corecrt_math.h>
#include <thread>

XennonStaticSpriteComponent::XennonStaticSpriteComponent(std::string TexturePath, int TilesX, int TilesY, Actor* ComponentOwner, int TextureIndexToDisplay) : SpriteComponent(TexturePath, TilesX, TilesY, 0, ComponentOwner)
{
	Owner = ComponentOwner;

	MyTransform = new Transform;
	MyTransform->IsRelative = true;

	DisplaySprite = GameplayStatics::CreateTextureFromSurface(TexturePath);

	GameplayStatics::QueryTexture(DisplaySprite, tw, th);

	TextureAmountH = TilesX;
	TextureAmountV = TilesY;

	fw = tw / TextureAmountH;
	fh = th / TextureAmountV;

	Quad.x = 0; Quad.y = 0;
	Quad.w = fw; Quad.h = fh;

	SetTextureIndexToDisplay(TextureIndexToDisplay);
}

void XennonStaticSpriteComponent::Tick(float DeltaSeconds)
{
	if (IsPlayingAnimation)
	{
		#pragma region Dimentions
		//TEXTURE POSITION -----------------------------------------------------------
		if (Owner != nullptr)
		{
			DisplayQuad.x = (int)MyTransform->GetLocation().X + (int)Owner->GetTransform()->GetLocation().X;
			DisplayQuad.y = (int)MyTransform->GetLocation().Y + (int)Owner->GetTransform()->GetLocation().Y;
		}
		else
		{
			DisplayQuad.x = (int)MyTransform->GetLocation().X;
			DisplayQuad.y = (int)MyTransform->GetLocation().Y;
		}



		//TEXTURE SCALE --------------------------------------------------------------
		// Quad Scale X = (Texture width / Texture Amount horizontally) * X Scale
		if (Owner != nullptr)
		{
			DisplayQuad.w = (int)((float)(tw / TextureAmountH) * (MyTransform->GetScale().X * Owner->GetTransform()->GetScale().X));
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / TextureAmountV) * (MyTransform->GetScale().Y * Owner->GetTransform()->GetScale().Y));
		}
		else
		{
			DisplayQuad.w = (int)((float)(tw / TextureAmountH) * MyTransform->GetScale().X);
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / TextureAmountV) * MyTransform->GetScale().Y);
		}



#pragma endregion

		GameplayStatics::RenderTexture(DisplaySprite, &Quad, &DisplayQuad);
	}
}

//this component does not loop, loop is irrelevant
void XennonStaticSpriteComponent::PlayAnimation(bool Loop)
{
	IsPlayingAnimation = true;
}

void XennonStaticSpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
}

void XennonStaticSpriteComponent::SetTextureIndexToDisplay(int NewIndex)
{
	_CurrentIndex = NewIndex;
	Quad.x = 0;
	Quad.y = 0;
	for (int i = 0; i < NewIndex - 1; ++i)
	{
		//Animation->Forward
		Quad.x += fw;
		if (Quad.x >= tw)
		{
			Quad.x = 0;
			Quad.y += fh;
			if (Quad.y >= th)
			{
				Quad.y = 0;
			}
		}
	}
}

void XennonStaticSpriteComponent::AnimTansitionToIndex(int Index, float TotalSeconds, bool *StateReset)
{
	int maxNumberOfLoops = abs(Index - _CurrentIndex);
	std::thread t1([=]() 
	{
		*StateReset = true;
		int loopCounter = 0;
		if (Index > _CurrentIndex)
		{	
			//++
			while (_CurrentIndex < Index && loopCounter <= maxNumberOfLoops)
			{
				if (_CurrentIndex < 0)
				{
					return;
				}
				GameplayStatics::Delay(fabs(TotalSeconds / (Index - _CurrentIndex)));
				SetTextureIndexToDisplay(_CurrentIndex + 1);
				loopCounter++;
			}
		}
		else
		{
			//--
			loopCounter = 0;
			while (_CurrentIndex > Index && loopCounter <= maxNumberOfLoops)
			{	
				if (_CurrentIndex < 0)
				{
					return;
				}
				GameplayStatics::Delay(fabs(TotalSeconds / (_CurrentIndex - Index)));
				SetTextureIndexToDisplay(_CurrentIndex - 1);
				loopCounter++;
			}
		}
		*StateReset = false;
	});
	t1.detach();
}
