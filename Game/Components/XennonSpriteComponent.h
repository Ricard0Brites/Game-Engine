#pragma once
#include "GameEngine.h"


class XennonStaticSpriteComponent : SpriteComponent
{

public:
	XennonStaticSpriteComponent(std::string TexturePath, int TilesX, int TilesY, Actor* ComponentOwner, int TextureIndexToDisplay);
	~XennonStaticSpriteComponent();


	virtual void Tick(float DeltaSeconds) override;

	virtual void PlayAnimation(bool Loop) override;

	virtual void StopAnimation() override;

	void SetTextureIndexToDisplay(int NewIndex);

	void AnimTansitionToIndex( int Index, float TotalSeconds, bool *StateReset);
private:
 int _CurrentIndex=0;
};