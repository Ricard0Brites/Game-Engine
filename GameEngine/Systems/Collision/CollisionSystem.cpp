#include "CollisionSystem.h"
#include "GameEngine.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::CheckCollision()
{
	auto ActorsList = &GameplayStatics::GetGameEngine()->_Actors;

	if(!ActorsList)
		return;

	for(Actor* Entity : *ActorsList)
	{
		for (Actor* ComparativeEntity : *ActorsList)
		{
			if(ComparativeEntity == Entity) // skip myself
				continue;

			if (Entity->CollisionRadius < 0 || ComparativeEntity->CollisionRadius < 0) // skip non collideable objects
				continue;

			if(Entity->IsLevelActor && ComparativeEntity->IsLevelActor) // ignore any level actor -> level actor collisions
				continue;
			if(!Entity->GetSpriteComponent() || !ComparativeEntity->GetSpriteComponent())
				continue;


			Vector Actor2CollisionComponentLocation = ComparativeEntity->GetTransform()->GetLocation() + Vector::CreateVector((float)(ComparativeEntity->GetSpriteComponent()->GetSpriteWidth() / 2), (float)(ComparativeEntity->GetSpriteComponent()->GetSpriteHeight() / 2), 0.f),
			Actor1CollisionComponentLocation = Entity->GetTransform()->GetLocation() + Vector::CreateVector((float)(Entity->GetSpriteComponent()->GetSpriteWidth() / 2), (float)(Entity->GetSpriteComponent()->GetSpriteHeight() / 2), 0.f);

			Vector RelativeActorLocation = Actor2CollisionComponentLocation - Actor1CollisionComponentLocation;
			float DistanceBetweenActors = GameplayStatics::GetVectorNorm(&RelativeActorLocation);

 			if(DistanceBetweenActors < Entity->CollisionRadius + ComparativeEntity->CollisionRadius)
 			{					
 				if(!Entity->IsPendingKill && !ComparativeEntity->IsPendingKill)
 				{
					Entity->OnCollisionStarted(ComparativeEntity);
					ComparativeEntity->OnCollisionStarted(Entity);
 				}
 			}
		}
	}
}
