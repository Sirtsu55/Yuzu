#pragma once


namespace Yuzu
{
	class Entity;
	
	class World
	{
	public:
		~World();
		World();
		

	
		void OnUpdate(float DeltaTime);

		
		

		
		static void SetAsCurrent(const Sptr<World>& NewWorld) { m_CurrentWorld = NewWorld.get(); }
		static World* GetWorld() { return m_CurrentWorld; }

		//Definition in Entity.cpp because of compile errors

		entt::entity CreateEntity();

	private:

		entt::registry m_Registry;
		
		static World* m_CurrentWorld;

		friend class Entity;

	};




}

