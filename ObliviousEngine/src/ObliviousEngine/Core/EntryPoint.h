#pragma once

#include "Application.h"
#include "Core.h"
#include "Log.h"

#ifdef PLATFORM_WINDOWS

extern OE::Application * OE::CreateApplication();

int main(int argc, char ** argv)
{
    OE::Log::Init();
    OE::Maths::Init();

    std::string profilePath = "profiling";
    bool logCreateSuccess = false;
#ifdef PROFILING_ENABLED
    if (std::filesystem::exists(profilePath))
    {
        std::filesystem::remove_all(profilePath);
        CORE_TRACE("Removing Profiling Folder");
    }
    logCreateSuccess = std::filesystem::create_directory(profilePath);

    if (!logCreateSuccess)
    {
        CORE_WARN("Warn: Could not create profiling folder. Profiling will be disabled for this run.");
    }
#endif // PROFILING_ENABLED

    if (logCreateSuccess)
    {
        START_PROFILER("Startup", profilePath + "/OEProfile-Startup.json");
    }
    CORE_TRACE("Main Started");
    auto app = OE::CreateApplication();
    if (logCreateSuccess)
    {
        STOP_PROFILER();
        START_PROFILER("Runtime", profilePath + "/OEProfile-Runtime.json");
    }
    CORE_TRACE("App created");
    app->run();
    CORE_TRACE("App ended.");
    if (logCreateSuccess)
    {
        STOP_PROFILER();
        START_PROFILER("Shutdown", profilePath + "/OEProfile-Shutdown.json");
    }
    delete app;
    if (logCreateSuccess)
    {
        STOP_PROFILER();
    }
    CORE_WARN("Warn: Engine shutting down.");
}

#endif // PLATFORM_WINDOWS
