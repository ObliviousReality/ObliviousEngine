#pragma once

#include <memory>
#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace OE {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static Ref<spdlog::logger> coreLogger;
		static Ref<spdlog::logger> clientLogger;
	};
}

#define OE_CORE_FATAL(...) ::OE::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define OE_CORE_ERROR(...) ::OE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OE_CORE_WARN(...)  ::OE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OE_CORE_INFO(...)  ::OE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OE_CORE_TRACE(...) ::OE::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define OE_FATAL(...) ::OE::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define OE_ERROR(...) ::OE::Log::GetClientLogger()->error(__VA_ARGS__)
#define OE_WARN(...)  ::OE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OE_INFO(...)  ::OE::Log::GetClientLogger()->info(__VA_ARGS__)
#define OE_TRACE(...) ::OE::Log::GetClientLogger()->trace(__VA_ARGS__)
