#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"


SpriteComponent::SpriteComponent()
{
	MyTransform = new Transform;
	MyTransform->IsRelative = true;
}

SpriteComponent::~SpriteComponent()
{
	delete MyTransform;
}

void SpriteComponent::Tick(float DelataSeconds)
{
	if (IsPlayingAnimation)
	{

	}
}

SDL_Texture* SpriteComponent::GetSpriteInLocation(std::string Path)
{	
	return SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), SDL_LoadBMP(&(Path)[0]));	
}

void SpriteComponent::PlayAnimation(bool Loop, float AnimationTotalTime, void(&OnCompleted)())
{
	
}

void SpriteComponent::PlayAnimationReverse(bool Loop, float AnimationTotalTime)
{

}

void SpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
	OnAnimationComplete();
}

void SpriteComponent::OnAnimationComplete()
{

}
