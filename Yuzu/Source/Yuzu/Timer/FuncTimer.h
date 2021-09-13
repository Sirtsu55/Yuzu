#pragma once
#include <vector>

namespace Yuzu
{



	//Wrapper class to allow templated versions of the actual FuncTimer class
	class _FuncTimerCore
	{
	public:


		static void UpdateTimers();

	private:
		static std::vector<_FuncTimerCore*> s_Timers;
		
		template<typename T>
		friend void CreateFunctionTimer(float TimeGap, T* Obj, bool(T::* Func)(void));


		virtual bool Update();
	};

	//Actual FuncTimer class 
	template<typename T>
	class _FuncTimer : public _FuncTimerCore
	{
	public:


		_FuncTimer(float TimeGap, T* Obj, bool(T::*Func)(void));
		~_FuncTimer();


	private:

		bool Update() override;

		T* m_Obj;
		bool(T::* m_Func)(void);
		float m_TGap;
		bool m_Active = true;
		
		std::chrono::steady_clock::time_point m_LastTime;

		friend void CreateFunctionTimer(float TimeGap, T* Obj, bool(T::* Func)(void));

	};

	template<typename T>
	inline _FuncTimer<T>::_FuncTimer(float TimeGap, T* Obj, bool(T::* Func)(void))
		: m_Obj(Obj), m_Func(Func), m_TGap(TimeGap), m_Active(true)
	{
		m_LastTime = std::chrono::high_resolution_clock::now();
	}

	template<typename T>
	bool _FuncTimer<T>::Update()
	{
		auto EndTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> Duration = EndTime - m_LastTime;

		if (Duration.count() > m_TGap)
		{
			return (m_Obj->*m_Func)();
		}
		return true;
	}







	template<typename T>
	void CreateFunctionTimer(float TimeGap, T* Obj, bool(T::* Func)(void))
	{
		//Creates a Timer that will be Added globally to the timer vector
		_FuncTimer<T>* Tim = new _FuncTimer<T>(TimeGap, Obj, Func);

		_FuncTimerCore::s_Timers.push_back(Tim);
	}








}