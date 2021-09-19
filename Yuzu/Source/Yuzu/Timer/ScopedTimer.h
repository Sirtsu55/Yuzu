#pragma once

#include "Timers.h"

namespace Yuzu
{

	class ScopedTimer
	{
		std::chrono::steady_clock::time_point m_StartTime;
		const char* m_TimerName;
		bool LogToConsole;
		

	public:
		ScopedTimer(const char* Name, bool logtoconsole = true);
		~ScopedTimer();

	};

}