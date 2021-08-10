#pragma once


namespace Yuzu
{
	class Entity;
	class Window;
	struct TimeStep
	{
		float Seconds = 0.0f;
		float Milliseconds = 0.0f;
		float MicroSeconds = 0.0f;

	};

	class World
	{
	public:
		~World();
		World();

		void OnUpdate(float DeltaTime);
		//Definition in Entity.cpp because of compile errors
		entt::entity CreateEntity();

		

		
		static void SetAsCurrent(const Sptr<World>& NewWorld) { m_CurrentWorld = NewWorld.get(); }
		static World* GetWorld() { return m_CurrentWorld; }
		static const TimeStep& GetTimeStep() { return FrameTimeStep; }
	private:
		entt::registry m_Registry;
		

		static TimeStep FrameTimeStep;
		static void RenderWorld();
		static World* m_CurrentWorld;

		friend class Entity;
		friend class Window;

	};




}

