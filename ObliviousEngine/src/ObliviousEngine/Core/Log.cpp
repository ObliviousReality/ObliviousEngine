#include "oepch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace OE
{
    Ref<spdlog::logger> Log::coreLogger;
    Ref<spdlog::logger> Log::clientLogger;

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d-%H-%M-%S");
        auto logName = "logs/" + oss.str() + ".log";

        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logName, true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        coreLogger = std::make_shared<spdlog::logger>("Engine", begin(logSinks), end(logSinks));
        spdlog::register_logger(coreLogger);
        coreLogger->set_level(spdlog::level::trace);

        clientLogger = std::make_shared<spdlog::logger>("Application", begin(logSinks), end(logSinks));
        spdlog::register_logger(clientLogger);
        clientLogger->set_level(spdlog::level::trace);
        clientLogger->flush_on(spdlog::level::trace);
    }
} // namespace OE
