#include "Core.h"
#include "ScopedTimer.h"

namespace Yuzu
{


	ScopedTimer::ScopedTimer(const char* Name, bool logtoconsole)
		:m_StartTime(std::chrono::high_resolution_clock::now()), m_TimerName(Name), LogToConsole(logtoconsole)
	{
	}


	ScopedTimer::~ScopedTimer()
	{
		auto EndTime = std::chrono::high_resolution_clock::now();
		if (LogToConsole)
		{
			std::chrono::duration<double, std::milli> Duration = (EndTime - m_StartTime);

			YZC_INFO("[TIMER]  [{0}][{1}:MS]", m_TimerName, Duration.count());
		}
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTime).time_since_epoch().count();


		TimerWriter::WriteToFile(m_TimerName, std::this_thread::get_id(), start, end);
	}

}

