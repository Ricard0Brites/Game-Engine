#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(Uint32 flags /*= 0*/)
{
	if (SDL_Init(flags) != 0)
		0;
}

SDLWrapper::~SDLWrapper()
{
	SDL_Quit();
}
