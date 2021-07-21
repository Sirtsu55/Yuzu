#pragma once
#include <chrono>


namespace Yuzu
{

	class Timer
	{
	public:
		enum class Accuracy
		{
			MilliSec,
			MicroSec,
			NanoSec,
			Seconds

		};

		Timer();
		~Timer();


		void Start();
		double End(Accuracy acc);
		double End();


	private:
		std::chrono::steady_clock::time_point StartTime;
		std::chrono::steady_clock::time_point EndTime;
	};
	static double GetElapsedSeconds();
	static double GetElapsedSeconds(Timer::Accuracy acc);
}



