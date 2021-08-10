#pragma once




namespace Yuzu
{


	struct Job
	{

		void(*Function)(void*);
		void* Data;

		Job(void(*Func)(void*), void* data)
			:Function(Func), Data(data) {}
		Job() = default;

		void Call()
		{
			(*Function)(Data);
		}

	};
	class JobHandler
	{
	public:
		JobHandler();
		~JobHandler();
		bool HasJobs() { return m_Jobs.empty(); }
		void AddJob(Job JobToAdd);

		void AddJob(void(*Function)(void*), void* Data);
		
		static void StopWork(bool* Cond);
	private:
		void Work();
		
		std::queue<Job> m_Jobs;
		std::thread m_Worker;
		bool DoWork = false;

	};

}
