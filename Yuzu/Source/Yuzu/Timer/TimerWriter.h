#pragma once


namespace Yuzu
{




	class TimerWriter
	{
	public:

		static void WriteToFile(const char* Name, const std::thread::id& ThreadID, const long long StartTime, const long long EndTime);


		static void StartSession(const std::string& SessionName);
		static void EndSession();

		static const char* GetSession() { return s_CurrentSession; }
	private:
		TimerWriter();
		~TimerWriter();

		static const char* s_CurrentSession;
		static std::ofstream s_OutputStream;
		static int s_ProfileCount;

	};

}