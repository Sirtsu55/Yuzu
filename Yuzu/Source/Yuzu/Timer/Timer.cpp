#include "Core.h"

#include "Timer.h"


namespace Yuzu 
{

	auto ProgramStartTime = std::chrono::high_resolution_clock::now();

	Timer::Timer()
	{
	}

	Timer::~Timer()
	{

	}

	void Timer::Start()
	{
		StartTime = std::chrono::high_resolution_clock::now();
	}
	/// Gives Time in Seconds
	double Timer::End()
	{
		EndTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> Duration = (EndTime - StartTime);
		return Duration.count();

	}
	/// Gives Time in Specified accuracy

	double Timer::End(Accuracy acc)
	{

		EndTime = std::chrono::high_resolution_clock::now();

		switch (acc)
		{
		case Accuracy::MilliSec:
			{
				std::chrono::duration<double, std::milli> Duration = EndTime - StartTime;
				return Duration.count();
				break;
			}
			case Accuracy::MicroSec:
			{
				std::chrono::duration<double, std::micro> Duration = EndTime - StartTime;
				return Duration.count();
				break;
			}
			case Accuracy::NanoSec:
			{
				std::chrono::duration<double, std::nano> Duration = EndTime - StartTime;
				return Duration.count();
				break;
			}
			case Accuracy::Seconds:
			{
				std::chrono::duration<double> Duration = EndTime - StartTime;
				return Duration.count();
				break;
			}

		}
		return -1;
	}




	double GetElapsedSeconds()
	{
		std::chrono::duration<double, std::milli> Duration = std::chrono::high_resolution_clock::now() - ProgramStartTime;

		return Duration.count();
	}


	double GetElapsedSeconds(Timer::Accuracy acc)
	{

		auto EndTime = std::chrono::high_resolution_clock::now();

		switch (acc)
		{
			case Timer::Accuracy::MilliSec:
			{
				std::chrono::duration<double, std::milli> Duration = EndTime - ProgramStartTime;
				return Duration.count();
				break;
			}
			case Timer::Accuracy::MicroSec:
			{
				std::chrono::duration<double, std::micro> Duration = EndTime - ProgramStartTime;
				return Duration.count();
				break;
			}
			case Timer::Accuracy::NanoSec:
			{
				std::chrono::duration<double, std::nano> Duration = EndTime - ProgramStartTime;
				return Duration.count();
				break;
			}
			case Timer::Accuracy::Seconds:
			{
				std::chrono::duration<double> Duration = EndTime - ProgramStartTime;
				return Duration.count();
				break;
			}
		}
		return -1;
	}
	

}