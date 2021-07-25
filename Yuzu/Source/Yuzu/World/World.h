#pragma once


namespace Yuzu
{
	class World
	{
	public:
		~World();
		static World* GetWorld();

	private:
		World();
		static World* WorldInstance;


		entt::registry m_Registry;
		



	};
}

