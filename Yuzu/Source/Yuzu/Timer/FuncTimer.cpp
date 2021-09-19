#include "Core.h"
#include "FuncTimer.h"


namespace Yuzu
{

	std::vector<_FuncTimerCore*> _FuncTimerCore::s_Timers;


	//Updates every timer and deletes if the function call returns false
	void _FuncTimerCore::UpdateTimers()
	{


		std::chrono::steady_clock::time_point EndTime = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < s_Timers.size(); i++)
		{
			if (s_Timers[i]->Update(EndTime) == false)
			{
				delete s_Timers[i];
				s_Timers.erase(s_Timers.begin() + i);
			}
		}
	}	
	bool _FuncTimerCore::Update(const std::chrono::steady_clock::time_point& EndTime)
	{

		return false;
	}


}