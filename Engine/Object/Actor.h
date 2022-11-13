#pragma once
#include "object.h"
#include "..\Data\DataTypes.h"

class Transform;

class Actor : Object
{
public:
	Actor();
	~Actor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnKeyPressed(SDL_KeyCode KeyCode) override;

	virtual Transform* GetTransform();

	bool HasInit = false;

protected:
	Transform* MyTransform;

};