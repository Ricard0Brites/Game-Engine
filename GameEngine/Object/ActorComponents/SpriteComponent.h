#pragma once

#include <list>
#include <string>
#include "Data\DataTypes.h"
#include "glew.h"
#include <vector>

using namespace std;

struct SDL_Texture;
class Transform;
class Vector;
class Actor;

struct Vertex
{
	/*Vertex Location*/ float x = 0, y = 0;
	/*Texture Coordinates*/ float tcx = 0, tcy = 0;
};

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
	//plays animation in reverse (X reverse, Y Keeps the order)
	virtual void PlayAnimationReverse(bool Loop);
	//stops animation from playing
	virtual void StopAnimation();
	//Plays Single Frame
	virtual void ShowFrame(int FrameIndex);

	int GetSpriteWidth() { return fw; }
	int GetSpriteHeight() { return fh; }

protected:
	//
	Transform* MyTransform = nullptr;
	SDL_Texture* DisplaySprite;
	SDL_Rect Quad;

	//Animation
	unsigned int frameCounter = 0;

	bool IsPlayingAnimation = false;
	int tw, th, fw, fh, ChannelCount;
	int TextureAmountH, TextureAmountV;
	bool LoopAnimation;

	//Single Frame
	bool PlaySingleFrame;
	int FrameToRender = 0;
	
	//Animation Timer
	float AnimationTimeInMS, ElapsedTime;
	Actor* Owner;
	SDL_Rect DisplayQuad;

private:
	bool _IsAnimationReverse = false;

	//OpenGL
	GLuint VAO, VBO, Texture;
	unsigned char* TextureData; // The Raw texture 
	//-------------------------------------------------------
	std::vector<float> Vertices = {};
	

	//-------------------------------------------------------


	Vector NormalizeLocation(Vector Location);
	void CreateVertices(float SpriteX, float SpriteY, int SpriteCountX, int SpriteCountY);
	void RenderSprite();
};

