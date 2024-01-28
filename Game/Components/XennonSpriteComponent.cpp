#pragma once
#include "XennonSpriteComponent.h"
#include <thread>
#include <corecrt_math.h>

XennonStaticSpriteComponent::XennonStaticSpriteComponent(std::string TexturePath, int TilesX, int TilesY, Actor* ComponentOwner, int TextureIndexToDisplay) : SpriteComponent(TexturePath, TilesX, TilesY, 0, ComponentOwner)
{
	Owner = ComponentOwner;
	ShowFrame(TextureIndexToDisplay);
}

void XennonStaticSpriteComponent::Tick(float DeltaSeconds)
{
	SpriteComponent::Tick(DeltaSeconds);
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

void XennonStaticSpriteComponent::AnimTansitionToIndex(int Index, float TotalSeconds, bool *StateReset)
{
	int maxNumberOfLoops = abs(Index - CurrentFrame);
	std::thread t1([=]() 
	{
		*StateReset = true;
		int loopCounter = 0;
		if (Index > CurrentFrame)
		{	
			//++
			while (CurrentFrame < Index && loopCounter <= maxNumberOfLoops)
			{
				if (CurrentFrame < 0)
				{
					return;
				}
				GameplayStatics::Delay(fabs(TotalSeconds / (Index - CurrentFrame)));
				ShowFrame(CurrentFrame + 1);
				loopCounter++;
			}
		}
		else
		{
			//--
			loopCounter = 0;
			while (CurrentFrame > Index && loopCounter <= maxNumberOfLoops)
			{	
				if (CurrentFrame < 0)
				{
					return;
				}
				GameplayStatics::Delay(fabs(TotalSeconds / (CurrentFrame - Index)));
				ShowFrame(CurrentFrame - 1);
				loopCounter++;
			}
		}
		*StateReset = false;
	});
	t1.detach();
}
