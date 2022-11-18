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

