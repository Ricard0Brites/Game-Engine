#pragma once

#include "GameEngine.h";

class TestActor : Actor
{
public:
	TestActor();
	~TestActor();


	virtual void BeginPlay() override
	{
		Actor::BeginPlay();
	}


	virtual void Tick(float DeltaSeconds) override
	{
		Actor::Tick(DeltaSeconds);
		std::cout << "TEST Actor";
	}


	virtual void OnKeyPressed(SDL_KeyCode KeyCode) override
	{
		
	}

private:

};

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}
