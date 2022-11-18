#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"


SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

SDL_Texture* SpriteComponent::GetSprite(std::string Path)
{
	return SDL_CreateTextureFromSurface(SDL_GetRenderer(GameplayStatics::GameEngineRef->GetWindow()), SDL_LoadBMP(&(Path)[0]));	
}

std::list<SDL_Texture*> SpriteComponent::DivideSprite(SDL_Texture* UndividedSprite, Uint8 HorizontalTileAmount, Uint8 VerticalTileAmount)
{
	
}

void SpriteComponent::PlayAnimation(bool Loop, float AnimationTotalTime)
{

}

void SpriteComponent::PlayAnimationReverse(bool Loop, float AnimationTotalTime)
{

}

void SpriteComponent::StopAnimation()
{

}

