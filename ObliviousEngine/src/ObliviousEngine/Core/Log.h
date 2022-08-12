#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace OE {
	class OBLIVIOUSENGINE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

#define OE_CORE_FATAL(...) ::OE::Log::getCoreLogger()->fatal(__VA_ARGS__)
#define OE_CORE_ERROR(...) ::OE::Log::getCoreLogger()->error(__VA_ARGS__)
#define OE_CORE_WARN(...)  ::OE::Log::getCoreLogger()->warn(__VA_ARGS__)
#define OE_CORE_INFO(...)  ::OE::Log::getCoreLogger()->info(__VA_ARGS__)
#define OE_CORE_TRACE(...) ::OE::Log::getCoreLogger()->trace(__VA_ARGS__)

#define OE_FATAL(...) ::OE::Log::getClientLogger()->fatal(__VA_ARGS__)
#define OE_ERROR(...) ::OE::Log::getClientLogger()->error(__VA_ARGS__)
#define OE_WARN(...)  ::OE::Log::getClientLogger()->warn(__VA_ARGS__)
#define OE_INFO(...)  ::OE::Log::getClientLogger()->info(__VA_ARGS__)
#define OE_TRACE(...) ::OE::Log::getClientLogger()->trace(__VA_ARGS__)
