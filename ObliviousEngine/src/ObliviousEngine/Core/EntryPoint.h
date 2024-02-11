#pragma once

#include "Application.h"
#include "Core.h"
#include "Log.h"

#ifdef OE_PLATFORM_WINDOWS

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
        OE_CORE_TRACE("Removing Profiling Folder");
    }
    logCreateSuccess = std::filesystem::create_directory(profilePath);

    if (!logCreateSuccess)
    {
        OE_CORE_WARN("Warn: Could not create profiling folder. Profiling will be disabled for this run.");
    }
#endif // PROFILING_ENABLED

    if (logCreateSuccess)
    {
        OE_START_PROFILER("Startup", profilePath + "/OEProfile-Startup.json");
    }
    OE_CORE_TRACE("Main Started");
    auto app = OE::CreateApplication();
    if (logCreateSuccess)
    {
        OE_STOP_PROFILER();
        OE_START_PROFILER("Runtime", profilePath + "/OEProfile-Runtime.json");
    }
    OE_CORE_TRACE("App created");
    app->run();
    OE_CORE_TRACE("App ended.");
    if (logCreateSuccess)
    {
        OE_STOP_PROFILER();
        OE_START_PROFILER("Shutdown", profilePath + "/OEProfile-Shutdown.json");
    }
    delete app;
    if (logCreateSuccess)
    {
        OE_STOP_PROFILER();
    }
    OE_CORE_WARN("Warn: Engine shutting down.");
}

#endif // OE_PLATFORM_WINDOWS
