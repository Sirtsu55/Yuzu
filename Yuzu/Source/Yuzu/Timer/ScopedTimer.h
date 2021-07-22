#pragma once

#include "Timers.h"

namespace Yuzu
{

	class ScopedTimer
	{
		std::chrono::steady_clock::time_point m_StartTime;
		const char* m_TimerName;
		

	public:
		ScopedTimer(const char* Name);
		~ScopedTimer();

	};

}