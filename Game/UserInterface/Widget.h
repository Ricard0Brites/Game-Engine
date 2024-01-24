#pragma once
#include "GameEngine.h"
#include <vector>

enum WidgetAnchorH
{
	DefaultH = 0,
	Left,
	Middle,
	Right
};
enum WidgetAnchorV
{
	DefaultV = 0,
	Top,
	Mid,
	Bottom
};

struct WidgetAlignment
{
	void SetAlignment(WidgetAnchorH H, WidgetAnchorV V)
	{
		HAlignment = H;
		VAlignment = V;
	}
	WidgetAnchorH GetHAlignment() { return HAlignment; }
	WidgetAnchorV GetVAlignment() { return VAlignment; }

private:
	WidgetAnchorH HAlignment;
	WidgetAnchorV VAlignment;

};

//each widget should be a section in the screen bottom right section, top left etc
class Widget : public Actor
{
public:
	Widget(Actor* Parent);
	~Widget();


	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetText(std::string NewText);

	WidgetAlignment Alignment;
	
private:
	std::vector<SpriteComponent*> AnimComponents;
	std::string TextToDisplay = "";
};