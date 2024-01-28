#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"
#include "SDL_opengl.h"
#include "Plugins\stb_image.h"


SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	Owner = ComponentOwner;

	MyTransform = new Transform;
	MyTransform->IsRelative = true;


	SDL_Surface* surface = GameplayStatics::LoadSurface(TexturePath, GameplayStatics::GetGameEngine()->GetRenderer());
	if(surface) SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
	
	DisplaySprite = SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), surface);
	
	SDL_FreeSurface(surface);

	SDL_QueryTexture(DisplaySprite, NULL, NULL, &tw, &th);
	SDL_DestroyTexture(DisplaySprite);

	TextureAmountX = TilesX;
	TextureAmountY = TilesY;

	fw = tw / max(TextureAmountX, 1);
	fh = th / max(TextureAmountY, 1);

	Quad.x = 0; Quad.y = 0;
	Quad.w = fw; Quad.h = fh;

	AnimationTimeInMS = AnimationTimeInSeconds * 1000;
	ElapsedTime = 0;

	#pragma region OpenGL

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertexShader);

	// Create fragment shader
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);

	// Link shaders into a program
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	MyTextureID = LoadTexture(TexturePath.c_str());

#pragma endregion
}

SpriteComponent::SpriteComponent()
{
	
}

SpriteComponent::~SpriteComponent()
{
	if(MyTransform)
	{
		delete MyTransform;
		MyTransform = nullptr;
	}

	// Delete shaders
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	// Delete shader program
	glDeleteProgram(ShaderProgram);

	// Delete Buffers
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	// Delete texture
	glDeleteTextures(1, &MyTextureID);


}

void SpriteComponent::Tick(float DeltaSeconds)
{
	
	if (IsPlayingAnimation)
	{

	#pragma region Animations
		ElapsedTime += DeltaSeconds;

		if (_IsAnimationReverse)
		{
			//play anim reverse
			if (ElapsedTime >= AnimationTimeInMS / (TextureAmountY * TextureAmountX))
			{
				ElapsedTime = 0;
				Quad.x -= fw;
				if (Quad.x < 0)
				{
					Quad.x = tw - fw;

					Quad.y -= fh;
					if (Quad.y > 0)
					{
						Quad.y = th - fh;
						if (!LoopAnimation) StopAnimation();
					}

				}
			}
		}
		else
		{
			//Animation->Forward
			if (ElapsedTime >= AnimationTimeInMS / (TextureAmountY * TextureAmountX))
			{
				ElapsedTime = 0;
				Quad.x += fw;
				if (Quad.x >= tw)
				{
					Quad.x = 0;
					Quad.y += fh;
					if (Quad.y >= th)
					{
						Quad.y = 0;
						if (!LoopAnimation) StopAnimation();
					}
				}
			}
		}
#pragma endregion


		//SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
	}

	if (PlaySingleFrame)
	{
		//TEXTURE POSITION -----------------------------------------------------------
		if (Owner != nullptr)
		{
			DisplayQuad.x = (int)MyTransform->GetLocation().X + (int)Owner->GetTransform()->GetLocation().X;
			DisplayQuad.y = (int)MyTransform->GetLocation().Y + (int)Owner->GetTransform()->GetLocation().Y;
		}
		else
		{
			DisplayQuad.x = (int)MyTransform->GetLocation().X;
			DisplayQuad.y = (int)MyTransform->GetLocation().Y;
		}



		//TEXTURE SCALE --------------------------------------------------------------
		// Quad Scale X = (Texture width / Texture Amount horizontally) * X Scale
		if (Owner != nullptr)
		{
			DisplayQuad.w = (int)((float)(tw / max(TextureAmountX, 1)) * (MyTransform->GetScale().X * Owner->GetTransform()->GetScale().X));
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / max(TextureAmountY, 1)) * (MyTransform->GetScale().Y * Owner->GetTransform()->GetScale().Y));
		}
		else
		{
			DisplayQuad.w = (int)((float)(tw / max(TextureAmountX, 1)) * MyTransform->GetScale().X);
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / max(TextureAmountY, 1)) * MyTransform->GetScale().Y);
		}


		//SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
	}

	UpdateVerticesLocations();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Use the shader program
	glUseProgram(ShaderProgram);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, MyTextureID);

	// Set uniform variables
	GLint resolutionLocation = glGetUniformLocation(ShaderProgram, "resolution");
	glUniform2f(resolutionLocation, (float)GameplayStatics::GetScreenWidth(), (float)GameplayStatics::GetScreenHeight());

	// Draw the sprite
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void SpriteComponent::SetLocation(Vector NewLocation, Actor* Owner)
{
	if (!Owner) 
	{
		MyTransform->SetLocation(NewLocation);
	}
	else
	{
		Vector* FinalVector = new Vector;
		FinalVector->Zero(true);

		// gets the absolute owner
		while (Owner->GetOwner())
		{
			*FinalVector += Owner->GetTransform()->GetLocation();
			Owner = Owner->GetOwner();
		}
		//adds all of the parent locations
		MyTransform->SetLocation(NewLocation + Owner->GetTransform()->GetLocation() + *FinalVector);
	}
}

void SpriteComponent::SetScale(Vector NewScale, Actor* Owner)
{
	if (!Owner)
	{
		MyTransform->SetScale(NewScale);
	}
	else
	{
		Vector* TempScale = new Vector;
		TempScale->Zero(true);

		while (Owner->GetOwner())
		{
			*TempScale *= Owner->GetTransform()->GetScale();
			Owner = Owner->GetOwner();
		}

		MyTransform->SetScale(NewScale * (*TempScale) * Owner->GetTransform()->GetScale());
	}
	
}

void SpriteComponent::PlayAnimation(bool Loop)
{
	
	_IsAnimationReverse = false;
	IsPlayingAnimation = true;
	LoopAnimation = Loop;
	
}

void SpriteComponent::PlayAnimationReverse(bool Loop)
{
	Quad.x = tw - fw;
	Quad.y = th - fh;
	LoopAnimation = Loop;
	IsPlayingAnimation = true;
	_IsAnimationReverse = true;
}

void SpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
}

void SpriteComponent::ShowFrame(int FrameIndex)
{
	FrameToRender = FrameIndex;
	Quad.x = FrameIndex * GetSpriteWidth();
	Quad.y = 0; // only should be used with 1D spritesheets
	PlaySingleFrame = true;
}

GLuint SpriteComponent::LoadTexture(const char* filePath)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (!data) {
		// Handle texture loading error
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate the texture
	if (nrChannels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	// Free image data
	stbi_image_free(data);

	return textureID;
}

void SpriteComponent::UpdateVerticesLocations()
{
	//usign a matrix here would be ideal, manually setting all of this could be avoided (time constraints)
	Vector CurrentLocation, CurrentScale;
	if (Owner)
	{
		CurrentLocation = Owner->GetTransform()->GetLocation() + Gettransform()->GetLocation();
		CurrentScale = Owner->GetTransform()->GetScale() * Gettransform()->GetScale();
	}
		
	else
	{
		CurrentLocation = Gettransform()->GetLocation();
		CurrentScale = Gettransform()->GetScale();
	}
	
	float SpriteStepX = 1.f / TextureAmountX;
	float SpriteStepY = 1.f / TextureAmountY;

	//Top Left
	vertices[0] = (CurrentLocation.X - (fw / 2) * CurrentScale.X);/* X */
	vertices[1] = (CurrentLocation.Y + (fh / 2) * CurrentScale.Y);/* Y */
	vertices[2] = 0;
	vertices[3] = 1;

	//Bottom Left
	vertices[4] = (CurrentLocation.X - (fw / 2) * CurrentScale.X);/* X */
	vertices[5] = (CurrentLocation.Y - (fh / 2) * CurrentScale.Y);/* Y */
	vertices[6] = 0;
	vertices[7] = 0;


	//Bottom Right
	vertices[8] = (CurrentLocation.X + (fw / 2) * CurrentScale.X);/* X */
	vertices[9] = (CurrentLocation.Y - (fh / 2) * CurrentScale.Y);/* Y */
	vertices[10] = 1;
	vertices[11] = 0;

	//Top Right
	vertices[12] = (CurrentLocation.X + (fw / 2) * CurrentScale.X);/* X */
	vertices[13] = (CurrentLocation.Y + (fh / 2) * CurrentScale.Y);/* Y */
	vertices[14] = 1;
	vertices[15] = 1;
}
