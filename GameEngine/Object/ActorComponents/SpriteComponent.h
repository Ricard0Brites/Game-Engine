#pragma once

#include <list>
#include <string>
#include <glew.h>
#include "Data\DataTypes.h"

using namespace std;

struct SDL_Texture;
class Transform;
class Vector;
class Actor;

class SpriteComponent
{
public:
	SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds, Actor* ComponentOwner);
	SpriteComponent();
	~SpriteComponent();

	virtual void Tick(float DeltaSeconds);

	// sets the Sprite Relative location to its parent
	void SetLocation(Vector NewLocation, Actor* Owner);
	void SetScale(Vector NewScale, Actor* Owner);
	//SDL Rect doesn't support Rotation

	//
	Transform* Gettransform() { return MyTransform; }

	//
	virtual void PlayAnimation(bool Loop);
	//stops animation from playing
	virtual void StopAnimation();
	//Plays Single Frame
	virtual void ShowFrame(int FrameIndex);

	GLuint LoadTexture(const char* filePath);
	int GetSpriteWidth() { return fw; }
	int GetSpriteHeight() { return fh; }
	void SetColorKey(float R, float G, float B) { CKR = R; CKG = G; CKB = B;}
protected:
	//
	Transform* MyTransform = nullptr;
	SDL_Texture* DisplaySprite;

	//Animation
	unsigned int frameCounter = 0;

	bool IsPlayingAnimation = false;
	int tw, th, fw, fh;
	int TextureAmountX, TextureAmountY;
	bool LoopAnimation;

	//Single Frame
	bool PlaySingleFrame;
	
	//Animation Timer
	float AnimationTimeInMS, ElapsedTime;
	Actor* Owner;

	float CKR = 255, CKG = 0, CKB = 255;

	int CurrentFrame = 0;
private:
	GLuint MyTextureID = 0, VBO = 0, VAO = 0;
	void UpdateVerticesLocations();
	float vertices[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	
};

