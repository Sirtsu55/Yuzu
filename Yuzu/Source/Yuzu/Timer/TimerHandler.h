#pragma once
#include "SimpleTimer.h"


namespace Yuzu
{
	template<typename T>
	class TimerHandler
	{
	public:
		TimerHandler(void(T::* F)(bool), float intervalInSeconds);
		TimerHandler(const TimerHandler&) = default;
		~TimerHandler();

	private:
		SimpleTimer m_Timer;
		T* m_Object;
		void(T::* Func)(void);
	};



}