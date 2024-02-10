#include "oepch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace OE
{

    Ref<spdlog::logger> Log::coreLogger;
    Ref<spdlog::logger> Log::clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("Oblivious Engine");
        coreLogger->set_level(spdlog::level::trace);
        clientLogger = spdlog::stdout_color_mt("Application");
        clientLogger->set_level(spdlog::level::trace);
    }

} // namespace OE
