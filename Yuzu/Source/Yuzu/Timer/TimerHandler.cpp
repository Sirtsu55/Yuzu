#include "Core.h"
#include "TimerHandler.h"

namespace Yuzu
{ 
	template<typename T>
	inline TimerHandler<T>::TimerHandler(void(T::* F)(bool), float intervalInSeconds)
	{
	}
}


