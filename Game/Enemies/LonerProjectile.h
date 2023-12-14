#pragma once
#include "GameEngine.h"

class Vector;

class LonerProjectile : public Actor
{
	public:
		LonerProjectile(Actor* Owner);

		virtual void Tick(float DeltaSeconds) override;

		virtual void BeginPlay() override;

		virtual void OnCollisionStarted(const Actor* OtherActor) override;
		
		void SetProjectileDirection(Vector Direction) { ProjectileMovementDirection = Direction; }

	private:
		Vector ProjectileMovementDirection;
};

