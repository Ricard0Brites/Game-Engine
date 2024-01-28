#include "Widget.h"
#include <vector>

#define NUMBERTEXTUREPATH "src/Sprites/Numbers.bmp"
#define LOWERCASETEXTUREPATH "src/Sprites/AlphabetLower.bmp"
#define UPPERCASETEXTUREPATH "src/Sprites/AlphabetUpper.bmp"


Widget::Widget(Actor* Parent) : Actor(Parent)
{

}

Widget::~Widget()
{
}

void Widget::Tick(float DeltaSeconds)
{
	__super::Tick(DeltaSeconds);

	for (SpriteComponent* SC : AnimComponents)
	{
		if(!SC)
			continue;
		SC->Tick(DeltaSeconds);
	}
}

void Widget::BeginPlay()
{
	__super::BeginPlay();
	//Center this acton on screen
	MyTransform->SetLocation(Vector::CreateVector((float)(GameplayStatics::GetScreenWidth() / 2), (float)(GameplayStatics::GetScreenHeight() / 2), 0.f));

	if (Alignment.GetHAlignment() == 0 || Alignment.GetVAlignment() == 0)
	{
		LOG("Widget Alignment is not set.", 3);
		EXECUTIONLOG;
	}
}

void Widget::SetText(std::string NewText)
{
	if (Alignment.GetHAlignment() == 0 || Alignment.GetVAlignment() == 0)
	{
		LOG("Widget Alignment is not set. Stopping Execution Widget::SetText(std::string NewText);", 3);
		EXECUTIONLOG;
		return;
	}
	
	std::vector<SpriteComponent*> Array(NewText.length());
	int i = 0;
	for (char Letter : NewText)
	{		
		if(Array[i])
			continue;

		const int CharAsciiCode = (int)Letter;
		int RealIndex = 0;
		
		std::string TexturePath;
		int TileAmountX = 0;

		if(CharAsciiCode >= 48 && CharAsciiCode <= 57)
		{
			TexturePath = NUMBERTEXTUREPATH;
			TileAmountX = 10;
			RealIndex = CharAsciiCode - 48;
		}
		else if(CharAsciiCode >= 65 && CharAsciiCode <= 90)
		{
			TexturePath = UPPERCASETEXTUREPATH;
			TileAmountX = 26;
			RealIndex = CharAsciiCode - 65;
		}
		else if (CharAsciiCode >= 97 && CharAsciiCode <= 122)
		{
			TexturePath = LOWERCASETEXTUREPATH;
			TileAmountX = 26;
			RealIndex = CharAsciiCode - 97;
		}

		Array[i] = new SpriteComponent(TexturePath, TileAmountX, 1, 0, nullptr);
		Array[i]->ShowFrame(RealIndex + 1);
		switch (Alignment.GetHAlignment())
		{
			case WidgetAnchorH::Left:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.X = (i * Array[i]->GetSpriteWidth());
				Array[i]->Gettransform()->SetLocation(Cache);
				break;
			}
			case WidgetAnchorH::Right:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.X = GameplayStatics::GetScreenWidth() - (i * Array[i]->GetSpriteWidth());
				Array[i]->Gettransform()->SetLocation(Cache);

				break;
			}
			case WidgetAnchorH::Middle:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.X = GameplayStatics::GetScreenWidth() / 2 + (i * Array[i]->GetSpriteWidth());
				Array[i]->Gettransform()->SetLocation(Cache);
				break;
			}
			default:
				break;
		}

		switch (Alignment.GetVAlignment())
		{
			case WidgetAnchorV::Top:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.Y = Array[i]->GetSpriteHeight();
				Array[i]->Gettransform()->SetLocation(Cache);

				break;
			}
			case WidgetAnchorV::Bottom:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.Y = GameplayStatics::GetScreenHeight() - Array[i]->GetSpriteHeight();
				Array[i]->Gettransform()->SetLocation(Cache);

				break;
			}
			case WidgetAnchorV::Mid:
			{
				Vector Cache = Array[i]->Gettransform()->GetLocation();
				Cache.Y = (GameplayStatics::GetScreenHeight() / 2) - (Array[i]->GetSpriteHeight() / 2);
				Array[i]->Gettransform()->SetLocation(Cache);

				break;
			}
			default:
				break;
		}

		Array[i]->Gettransform()->SetLocation(Array[i]->Gettransform()->GetLocation() + Vector::CreateVector(20.f, -10.f, 0));
		++i;
	}
	AnimComponents = Array;
}
