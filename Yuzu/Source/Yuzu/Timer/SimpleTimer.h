#pragma once
#include <chrono>


namespace Yuzu
{

	enum class TimerAccuracy
	{
		MilliSec,
		MicroSec,
		NanoSec,
		Seconds

	};

	class SimpleTimer
	{
	public:
		SimpleTimer();
		~SimpleTimer();


		void Start();
		double End(TimerAccuracy acc);
		double End();


	private:
		std::chrono::steady_clock::time_point StartTime;
		std::chrono::steady_clock::time_point EndTime;
	};
	double GetElapsedSeconds();
	double GetElapsedSeconds(TimerAccuracy acc);
}



