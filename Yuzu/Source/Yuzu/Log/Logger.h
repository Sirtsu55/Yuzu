#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Yuzu
{
	class Log
	{
	private:
		Log() = delete;
		~Log() = delete;


		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	public:

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		


	};


}