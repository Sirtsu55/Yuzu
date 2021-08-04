#pragma once
#include "Yuzu/World/Entities/Entity.h"

namespace Yuzu
{
	
	class Entity;

	
	struct TickComponent
	{

		TickComponent() = default;
		TickComponent(Entity* Ent)
			: EntityObject(Ent)
		{
		
		}

		~TickComponent() = default;

		TickComponent(const TickComponent&) = default;


		void Update(float DeltaTime)
		{
			if (EntityObject->IsValid())
			{
			
				EntityObject->Update(DeltaTime);
			}
		}

		Entity* EntityObject = nullptr;

	};
}