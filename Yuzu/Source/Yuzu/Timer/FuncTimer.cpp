#include "Core.h"
#include "FuncTimer.h"


namespace Yuzu
{

	std::vector<_FuncTimerCore*> _FuncTimerCore::s_Timers;


	void _FuncTimerCore::UpdateTimers()
	{

		//Updates every timer and deletes if the function call returns false

		for (int i = 0; i < s_Timers.size(); i++)
		{
			if (s_Timers[i]->Update() == false)
			{
				delete s_Timers[i];
				s_Timers.erase(s_Timers.begin() + i);
			}
		}
	}	
	bool _FuncTimerCore::Update()
	{

		return false;
	}


}