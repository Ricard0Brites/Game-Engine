#pragma once
#include "GameEngine.h"

#include <iostream>
using namespace std;

class thread;

class XennonStaticSpriteComponent : SpriteComponent
{

public:
	XennonStaticSpriteComponent(std::string TexturePath, int TilesX, int TilesY, Actor* ComponentOwner, int TextureIndexToDisplay);

	virtual void Tick(float DeltaSeconds) override;

	virtual void PlayAnimation(bool Loop) override;

	virtual void StopAnimation() override;

	void SetTextureIndexToDisplay(int NewIndex);

	void AnimTansitionToIndex( int Index, float TotalSeconds, bool *StateReset);

	int GetTextureHeight() { return fh; }
	int GetTextureWidth() { return fw; }
private:
	int _CurrentIndex = 0;
};