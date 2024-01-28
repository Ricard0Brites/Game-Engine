#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"
#include "SDL_opengl.h"
#include "Data\DataTypes.h"
#include "Plugins\stb_image.h"


SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	Owner = ComponentOwner;
	MyTransform = new Transform;
	MyTransform->IsRelative = true;

	TextureAmountX = TilesX;
	TextureAmountY = TilesY;

	AnimationTimeInMS = AnimationTimeInSeconds * 1000;
	ElapsedTime = 0;

	#pragma region OpenGL

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(1);

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
		if (!PlaySingleFrame)
		{
			ElapsedTime += DeltaSeconds;
			if (ElapsedTime > (AnimationTimeInMS / (TextureAmountX * TextureAmountY)))
			{
				ElapsedTime = 0;
				CurrentFrame++;
				if (CurrentFrame > (TextureAmountX * TextureAmountY))
				{
					CurrentFrame = 1;
					if(!LoopAnimation)
						StopAnimation();
				}
			}
		}
		
		UpdateVerticesLocations();

		#pragma region Render
		// Use the shader program
		glUseProgram(*GameplayStatics::GetGameEngine()->GetShader());

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, MyTextureID);

		// Set uniform variables
		GLint resolutionLocation = glGetUniformLocation(*GameplayStatics::GetGameEngine()->GetShader(), "resolution");
		glUniform2f(resolutionLocation, (float)GameplayStatics::GetScreenWidth(), (float)GameplayStatics::GetScreenHeight());

		// Set texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Draw the sprite
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
#pragma endregion

	}
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
	IsPlayingAnimation = true;
	LoopAnimation = Loop;
	
}

void SpriteComponent::StopAnimation()
{
	IsPlayingAnimation = false;
}

void SpriteComponent::ShowFrame(int FrameIndex)
{
	CurrentFrame = FrameIndex;
	LoopAnimation = true;
 	PlaySingleFrame = true;
	IsPlayingAnimation = true;
 }

GLuint SpriteComponent::LoadTexture(const char* filePath)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filePath, &width, &height, &channels, STBI_rgb);
	if(!image)
		return -1;

	tw = width;
	th = height;
	fw = width / max(TextureAmountX, 1);
	fh = height / max(TextureAmountY, 1);
	
	// Create a new array for RGBA
	unsigned char* imageDataRGBA = new unsigned char[width * height * 4];

	// Color keying: Remove background color (RGB: 255, 0, 255)
	for (int i = 0; i < width * height; ++i)
	{
		if (image[i * 3] == CKR && image[i * 3 + 1] == CKG && image[i * 3 + 2] == CKB) 
		{
			// Set alpha channel to 0 to make the pixel transparent
			imageDataRGBA[i * 4] = imageDataRGBA[i * 4 + 1] = imageDataRGBA[i * 4 + 2] = imageDataRGBA[i * 4 + 3] = 0;
		}
		else 
		{
			// Copy RGB values and set alpha to 255
			imageDataRGBA[i * 4] = image[i * 3];
			imageDataRGBA[i * 4 + 1] = image[i * 3 + 1];
			imageDataRGBA[i * 4 + 2] = image[i * 3 + 2];
			imageDataRGBA[i * 4 + 3] = 255;  // Set alpha to 255 (fully opaque)
		}
	}

	// Generate OpenGL texture
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Load modified image data into the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageDataRGBA);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up
	stbi_image_free(image);
	delete[] imageDataRGBA;

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

	float SpriteStepX = 1.0f / static_cast<float>(max(TextureAmountX, 1));
	float SpriteStepY = 1.0f / static_cast<float>(max(TextureAmountY, 1));

	float CurrentFrameX = fmod(static_cast<float>(max(CurrentFrame, 1) - 1), static_cast<float>(max(TextureAmountX, 1)));
	float CurrentFrameY = floor(static_cast<float>(max(CurrentFrame, 1) - 1) / static_cast<float>(max(TextureAmountX, 1)));

	//Top Left
	vertices[0] = CurrentLocation.X - (max(fw, 1) / 2) * CurrentScale.X;    /* X */
	vertices[1] = CurrentLocation.Y + (max(fh, 1) / 2) * CurrentScale.Y;    /* Y */
	vertices[2] = CurrentFrameX * SpriteStepX;
	vertices[3] = 1.0f - (CurrentFrameY * SpriteStepY);

	//Bottom Left
	vertices[4] = CurrentLocation.X - (max(fw, 1) / 2) * CurrentScale.X;    /* X */
	vertices[5] = CurrentLocation.Y - (max(fh, 1) / 2) * CurrentScale.Y;    /* Y */
	vertices[6] = CurrentFrameX * SpriteStepX;
	vertices[7] = 1.0f - ((CurrentFrameY + 1.0f) * SpriteStepY);

	//Bottom Right
	vertices[8] = CurrentLocation.X + (max(fw, 1) / 2) * CurrentScale.X;    /* X */
	vertices[9] = CurrentLocation.Y - (max(fh, 1) / 2) * CurrentScale.Y;    /* Y */
	vertices[10] = (CurrentFrameX + 1.0f) * SpriteStepX;
	vertices[11] = 1.0f - ((CurrentFrameY + 1.0f) * SpriteStepY);

	//Top Right
	vertices[12] = CurrentLocation.X + (max(fw, 1) / 2) * CurrentScale.X;   /* X */
	vertices[13] = CurrentLocation.Y + (max(fh, 1) / 2) * CurrentScale.Y;   /* Y */
	vertices[14] = (CurrentFrameX + 1.0f) * SpriteStepX;
	vertices[15] = 1.0f - (CurrentFrameY * SpriteStepY);

}
