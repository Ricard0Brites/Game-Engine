#pragma once

#include <list>
#include <string>
#include "Data\DataTypes.h"
#include <glew.h>

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
	//plays animation in reverse (X reverse, Y Keeps the order)
	virtual void PlayAnimationReverse(bool Loop);
	//stops animation from playing
	virtual void StopAnimation();
	//Plays Single Frame
	virtual void ShowFrame(int FrameIndex);

	GLuint LoadTexture(const char* filePath);
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
	int tw, th, fw, fh;
	int TextureAmountX, TextureAmountY;
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
	int CurrentFrame = 0;

	GLuint MyTextureID = 0, ShaderProgram = 0, VBO = 0, VAO = 0;
	GLuint VertexShader, FragmentShader;
	void UpdateVerticesLocations();
	float vertices[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#pragma region Shaders Source

	const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    layout (location = 1) in vec2 texCoords;
    out vec2 TexCoords;

    uniform vec2 resolution; // Screen resolution

    void main()
    {
        gl_Position = vec4(position.x / resolution.x * 2.0 - 1.0, (position.y / resolution.y * 2.0 - 1.0) * -1, 0.0, 1.0);
        TexCoords = texCoords;
    }
)";

	const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform sampler2D spriteTexture;

    void main()
    {
        FragColor = texture(spriteTexture, TexCoords);
    }
)";
#pragma endregion
	
};

