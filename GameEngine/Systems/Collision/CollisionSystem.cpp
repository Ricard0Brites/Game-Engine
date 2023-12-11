#include "CollisionSystem.h"
#include "GameEngine.h"

#define LISTCONTAINS(list, Content) std::find(list.begin(), list.end(), Content) != list.end()

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

			if(Entity->CollisionRadius == -1 || ComparativeEntity->CollisionRadius == -1 ) // skip non collideable objects
				continue;

			if(Entity->ActorsInRange.size() <= 0) // if there are no actors in range skip
				continue;

			if(LISTCONTAINS(Entity->ActorsInRange, ComparativeEntity) || LISTCONTAINS(ComparativeEntity->ActorsInRange, Entity)) //skip if either actor is already present in eithers list
				continue;

			Vector RelativeActorLocation = ComparativeEntity->GetTransform()->GetLocation() - Entity->GetTransform()->GetLocation();
			float DistanceBetweenActors =  GameplayStatics::GetVectorNorm(&RelativeActorLocation);

			if(DistanceBetweenActors < Entity->CollisionRadius)
			{
				Entity->OnCollisionStarted(ComparativeEntity);
				Entity->ActorsInRange.push_front(ComparativeEntity);
				
				ComparativeEntity->OnCollisionStarted(Entity);
				ComparativeEntity->ActorsInRange.push_front(Entity);
			}
		}
	}
}
