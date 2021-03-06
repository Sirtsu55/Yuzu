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
		double Endd(TimerAccuracy acc);
		double Endd();

		float Endf(TimerAccuracy acc);
		float Endf();


	private:
		std::chrono::steady_clock::time_point StartTime;
		std::chrono::steady_clock::time_point EndTime;
	};
	double GetElapsedSeconds();
}



