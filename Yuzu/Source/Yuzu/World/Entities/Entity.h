#pragma once
#include "Yuzu/World/World.h"

#define Entity_Function(F) reinterpret_cast<void(Entity::*)(void)>(&F)

namespace Yuzu
{

	class Entity
	{

	private:
		entt::entity m_EntityID;
		World* m_World;




	public:
		Entity(entt::entity entityid, World* world);
		Entity(World* world);
		Entity() : m_EntityID(entt::null), m_World(nullptr) {}


		virtual ~Entity()
		{
			if (IsValid())
			{
				m_World->m_Registry.destroy(m_EntityID);
				
			}
		}


		template<typename T>
		bool HasComponent() 
		{ 
			return m_World->m_Registry.any_of<T>(m_EntityID); 
		}
		
		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args)
		{
			return m_World->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		}


		template<typename T>
		T& GetComponent()
		{
		
			return m_World->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		void RemoveComponent()

		{
			m_World->m_Registry.remove<T>(m_EntityID);
		}

		template<typename T>
		T* GetPtrToComponent()
		{
			T& Cmp = m_World->m_Registry.get<T>(m_EntityID);
			return &Cmp;
		}


		void SetLocation(glm::vec3 Location);

		bool IsValid() const
		{
			return m_World->m_Registry.valid(m_EntityID);
		}
		virtual void Update(float DeltaTime) = 0;




	};



}