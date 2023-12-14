#pragma once
#include "Object/Actor.h"
#include "Data/DataTypes.h"

enum InputKeyCodes;

class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	void TriggerTick(Actor* actor, float DeltaSeconds);
	void TriggerBeginPlay(Actor* actor);
	void TriggerOnInputPress(InputKeyCodes KeyCode);
	void TriggerOnInputRelease(InputKeyCodes KeyCode);
	void TriggerOnInputAxis(InputKeyCodes KeyCode, Vector Data);
};