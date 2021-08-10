#include "Core.h"
#include "JobHandler.h"



namespace Yuzu
{


	JobHandler::JobHandler()
	{
		m_Worker = std::thread(&JobHandler::Work, this);
	}

	JobHandler::~JobHandler()
	{
		DoWork = false;
		m_Worker.detach();
	}

	void JobHandler::Work()
	{
		DoWork = true;
		while (DoWork)
		{
			if (!m_Jobs.empty())
			{
				m_Jobs.front().Call();
				m_Jobs.pop();
			}
		}


	}


	void JobHandler::AddJob(Job JobToAdd)
	{
		m_Jobs.push(JobToAdd);
	}

	void JobHandler::AddJob(void(*Function)(void*), void* Data)
	{
		m_Jobs.emplace(Function, Data);
	}

	void JobHandler::StopWork(bool* Cond)
	{
		*Cond = false;
	}

}
