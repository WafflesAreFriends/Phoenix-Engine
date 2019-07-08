#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Phoenix {

	class PHOENIX_API Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
// Wrap errors in macro enabling on certain circumstances
#define PHX_CORE_INFO(...) ::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PHX_CORE_TRACE(...) ::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PHX_CORE_WARN(...) ::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PHX_CORE_ERROR(...) ::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PHX_CORE_FATAL(...) ::Phoenix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PHX_INFO(...) ::Phoenix::Log::GetClientLogger()->info(__VA_ARGS__)
#define PHX_TRACE(...) ::Phoenix::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PHX_WARN(...) ::Phoenix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PHX_ERROR(...) ::Phoenix::Log::GetClientLogger()->error(__VA_ARGS__)
#define PHX_FATAL(...) ::Phoenix::Log::GetClientLogger()->fatal(__VA_ARGS__)