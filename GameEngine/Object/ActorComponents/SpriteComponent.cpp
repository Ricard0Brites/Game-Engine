#include "SpriteComponent.h"
#include "SDL.h"
#include "..\..\GameEngine.h"
#include "STB/stb_image.h"



SpriteComponent::SpriteComponent(std::string TexturePath, int TilesX, int TilesY, float AnimationTimeInSeconds, Actor* ComponentOwner)
{
	Owner = ComponentOwner;

	MyTransform = new Transform;
	MyTransform->IsRelative = true;

	#pragma region SDL Logic
// 	SDL_Surface* surface = GameplayStatics::LoadSurface(TexturePath, GameplayStatics::GetGameEngine()->GetRenderer());
// 	if (surface) SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
// 
// 	DisplaySprite = SDL_CreateTextureFromSurface(GameplayStatics::GetGameEngine()->GetRenderer(), surface);
// 
// 	SDL_FreeSurface(surface);
// 
// 	SDL_QueryTexture(DisplaySprite, NULL, NULL, &tw, &th);
#pragma endregion

	#pragma region OpenGL Logic
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	TextureData = stbi_load(TexturePath.c_str(), &tw, &th, &ChannelCount, 3);
	if (TextureData)
	{
 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
 		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(TextureData);

	// Generate and bind the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind the Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Reserve space for the vertex data (GL_DYNAMIC_DRAW is used for frequently updated data)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), nullptr, GL_DYNAMIC_DRAW);

	// Specify vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	#pragma endregion

	

	TextureAmountH = TilesX;
	TextureAmountV = TilesY;

	fw = tw / max(TextureAmountH, 1);
	fh = th / max(TextureAmountV, 1);

	Quad.x = 0; Quad.y = 0;
	Quad.w = fw; Quad.h = fh;

	AnimationTimeInMS = AnimationTimeInSeconds * 1000;
	ElapsedTime = 0;
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
	SDL_DestroyTexture(DisplaySprite);
}

void SpriteComponent::Tick(float DeltaSeconds)
{
	
	if (IsPlayingAnimation)
	{
		//update animations each frame
		#pragma region Dimentions
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
				DisplayQuad.w = (int)((float)(tw / TextureAmountH) * (MyTransform->GetScale().X * Owner->GetTransform()->GetScale().X));
				// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
				DisplayQuad.h = (int)((float)(th / TextureAmountV) * (MyTransform->GetScale().Y * Owner->GetTransform()->GetScale().Y));
			}
			else
			{
				DisplayQuad.w = (int)((float)(tw / TextureAmountH) * MyTransform->GetScale().X);
				// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
				DisplayQuad.h = (int)((float)(th / TextureAmountV) * MyTransform->GetScale().Y);
			}
		


		#pragma endregion

		#pragma region Animations
			ElapsedTime += DeltaSeconds;

			if (_IsAnimationReverse)
			{
				//play anim reverse
				if (ElapsedTime >= AnimationTimeInMS / (TextureAmountV * TextureAmountH))
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
				if (ElapsedTime >= AnimationTimeInMS / (TextureAmountV * TextureAmountH))
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

		//Updates Locations
		CreateVertices((float)max(tw, 1) / (float)max(TextureAmountH, 1), (float)max(th, 1) / (float)max(TextureAmountV, 1), TextureAmountH, TextureAmountV);
		RenderSprite();
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
			DisplayQuad.w = (int)((float)(tw / max(TextureAmountH, 1)) * (MyTransform->GetScale().X * Owner->GetTransform()->GetScale().X));
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / max(TextureAmountV, 1)) * (MyTransform->GetScale().Y * Owner->GetTransform()->GetScale().Y));
		}
		else
		{
			DisplayQuad.w = (int)((float)(tw / max(TextureAmountH, 1)) * MyTransform->GetScale().X);
			// Quad Scale y = (Texture height / Texture Amount vertically) * Y Scale
			DisplayQuad.h = (int)((float)(th / max(TextureAmountV, 1)) * MyTransform->GetScale().Y);
		}


		SDL_RenderCopy(GameplayStatics::GetGameEngine()->GetRenderer(), DisplaySprite, &Quad, &DisplayQuad);
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

Vector SpriteComponent::NormalizeLocation(Vector Location)
{
	float RX, RY;
	RX = (float)GameplayStatics::GetScreenWidth();
	RY = (float)GameplayStatics::GetScreenHeight();

	return Vector::CreateVector(Location.X / RX, Location.Y / RY, Location.Z);
}

void SpriteComponent::CreateVertices(float SpriteX, float SpriteY, int SpriteCountX, int SpriteCountY)
{
	Vertex TL, TR, BL, BR;
	Vertices.clear();

	#pragma region Top Left
	{
		//Location
		TL.x = NormalizeLocation(Gettransform()->GetLocation()).X * Gettransform()->GetScale().X;
		TL.y = NormalizeLocation(Gettransform()->GetLocation()).Y * Gettransform()->GetScale().Y;
		//Tex Coords (will be the first sprite when init)
		TL.tcx = 0;
		TL.tcy = 1;

		Vertices.push_back(TL.x);
		Vertices.push_back(TL.y);
		Vertices.push_back(TL.tcx);
		Vertices.push_back(TL.tcy);
	}
#pragma endregion

	#pragma region Bottom Left
	{
		Vector NewVertexLocation = Gettransform()->GetLocation();
		NewVertexLocation.Y -= SpriteY;
		//Location
		BL.x = NormalizeLocation(NewVertexLocation).X * Gettransform()->GetScale().X;
		BL.y = NormalizeLocation(NewVertexLocation).Y * Gettransform()->GetScale().Y;
		//Tex Coords (will be the first sprite when init)
		BL.tcx = 0;
		BL.tcy = 0;

		Vertices.push_back(BL.x);
		Vertices.push_back(BL.y);
		Vertices.push_back(BL.tcx);
		Vertices.push_back(BL.tcy);
	}
#pragma endregion

	#pragma region Top Right
	{
		Vector NewVertexLocation = Gettransform()->GetLocation();
		NewVertexLocation.X += SpriteX;

		//Location
		TR.x = NormalizeLocation(NewVertexLocation).X * Gettransform()->GetScale().X;
		TR.y = NormalizeLocation(NewVertexLocation).Y * Gettransform()->GetScale().Y;
		//Tex Coords (will be the first sprite when init)
		TR.tcx = 1;
		TR.tcy = 1;

		Vertices.push_back(TR.x);
		Vertices.push_back(TR.y);
		Vertices.push_back(TR.tcx);
		Vertices.push_back(TR.tcy);
	}
#pragma endregion

	#pragma region Bottom Right
	{
		Vector NewVertexLocation = Gettransform()->GetLocation();
		NewVertexLocation.X += SpriteX;
		NewVertexLocation.Y += SpriteY;
		//Location
		BR.x = NormalizeLocation(NewVertexLocation).X * Gettransform()->GetScale().X;
		BR.y = NormalizeLocation(NewVertexLocation).Y * Gettransform()->GetScale().Y;
		//Tex Coords (will be the first sprite when init)
		BR.tcx = 1;
		BR.tcy = 0;

		Vertices.push_back(BR.x);
		Vertices.push_back(BR.y);
		Vertices.push_back(BR.tcx);
		Vertices.push_back(BR.tcy);
	}
	#pragma endregion
}

void SpriteComponent::RenderSprite()
{
	//Update the VBO vertices data
	
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Update the data in the VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), &Vertices);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}
