#pragma once

#include <memory>
#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace OE
{
    class Log
    {
    public:
        static void Init();

        inline static Ref<spdlog::logger> & GetCoreLogger() { return coreLogger; }
        inline static Ref<spdlog::logger> & GetClientLogger() { return clientLogger; }

    private:
        static Ref<spdlog::logger> coreLogger;
        static Ref<spdlog::logger> clientLogger;
    };
} // namespace OE

#define CORE_FATAL(...) ::OE::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CORE_ERROR(...) ::OE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_WARN(...)  ::OE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_INFO(...)  ::OE::Log::GetCoreLogger()->info(__VA_ARGS__)
#ifdef LOG_TRACES
#define CORE_TRACE(...) ::OE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#else
#define CORE_TRACE(...)
#endif // LOG_TRACES


#define FATAL(...) ::OE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...) ::OE::Log::GetClientLogger()->error(__VA_ARGS__)
#define WARN(...)  ::OE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define INFO(...)  ::OE::Log::GetClientLogger()->info(__VA_ARGS__)
#define TRACE(...) ::OE::Log::GetClientLogger()->trace(__VA_ARGS__)
#ifdef LOG_TRACES
#define TRACE(...) ::OE::Log::GetClientLogger()->trace(__VA_ARGS__)
#else
#define TRACE(...)
#endif // LOG_TRACES
