#include "Core.h"
#include "Entity.h"
#include "World/Components/Components.h"


namespace Yuzu
{
	//Create Entity From World.h
	entt::entity World::CreateEntity()
	{
		return m_Registry.create();
	}



	Entity::Entity(entt::entity entityid, World* world)
		: m_EntityID(entityid), m_World(world)
	{

	}

	Entity::Entity(World* world)
		:  m_World(world)
	{
		m_EntityID = world->CreateEntity();
	}

	void Entity::SetLocation(glm::vec3 NewLocation)
	{
		
		if (auto* TransComp = m_World->m_Registry.try_get<TransformComponent>(m_EntityID))
		{
			TransComp->SetLocation(NewLocation);

		}
	}
	
	

}