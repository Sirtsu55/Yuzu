#include "Core.h"
#include "TimerWriter.h"

namespace Yuzu
{
	const char* TimerWriter::s_CurrentSession = "";
	std::ofstream TimerWriter::s_OutputStream;
	int TimerWriter::s_ProfileCount = 0;

	void TimerWriter::WriteToFile(const char* Name, const std::thread::id& ThreadID, const long long StartTime, const long long EndTime)
	{
		
		if (s_ProfileCount++ > 0)
			s_OutputStream << ",";

		if (s_CurrentSession != "")
		{
			s_OutputStream << "{";
			s_OutputStream << "\"cat\":\"function\",";
			s_OutputStream << "\"dur\":" << (EndTime - StartTime) << ',';
			s_OutputStream << "\"name\":\"" << Name << "\",";
			s_OutputStream << "\"ph\":\"X\",";
			s_OutputStream << "\"pid\":0,";
			s_OutputStream << "\"tid\":" << ThreadID << ",";
			s_OutputStream << "\"ts\":" << StartTime;
			s_OutputStream << "}";


			s_OutputStream.flush();


		}
		
	}

	void TimerWriter::StartSession(const std::string& SessionName)
	{
		s_CurrentSession = SessionName.c_str();
		s_OutputStream.open(SessionName + std::string(".json"));
		s_OutputStream << "[";
		s_OutputStream.flush();
	}

	void TimerWriter::EndSession()
	{
		s_CurrentSession = "";
		s_OutputStream << "]";
		s_OutputStream.flush();

		s_OutputStream.close();

	}

}