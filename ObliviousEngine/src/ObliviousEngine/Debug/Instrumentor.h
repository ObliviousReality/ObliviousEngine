//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in
//     profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile
// name.
//
#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace OE
{

    using floatms = std::chrono::duration<double, std::micro>;

    struct ProfileResult
    {
        std::string Name;
        floatms Start;
        std::chrono::microseconds ElapsedTime;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        std::mutex mutex;
        InstrumentationSession * m_CurrentSession;
        std::ofstream m_OutputStream;

    public:
        Instrumentor() : m_CurrentSession(nullptr) {}

        void StartSession(const std::string & name, const std::string & filepath = "results.json")
        {
            std::lock_guard lock(mutex);
            if (m_CurrentSession)
            {
                if (Log::GetCoreLogger())
                {
                    OE_CORE_ERROR("Instrumentor::BeginSession('{0}') WHEN SESSION '{1}' ALREADY OPEN",
                                  name,
                                  m_CurrentSession->Name);
                    InternalEndSession();
                }
            }
            m_OutputStream.open(filepath);
            if (m_OutputStream.is_open())
            {
                m_CurrentSession = new InstrumentationSession { name };
                WriteHeader();
            }
            else
            {
                if (Log::GetCoreLogger())
                {
                    OE_CORE_ASSERT("INSTRUMENTOR COULD NOT OPEN FILE '{0}'.", filepath);
                }
            }
        }

        void StopSession()
        {
            std::lock_guard lock(mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult & result)
        {
            /*if (m_ProfileCount++ > 0)
                m_OutputStream << ",";*/
            std::stringstream json;

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            json << std::setprecision(3) << std::fixed;
            json << "{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.ThreadID << ",";
            json << "\"ts\":" << result.Start.count();
            json << "}";

            std::lock_guard lock(mutex);
            if (m_CurrentSession)
            {
                m_OutputStream << json.str();
                m_OutputStream.flush();
            }
        }

        static Instrumentor & Get()
        {
            static Instrumentor instance;
            return instance;
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        void InternalEndSession()
        {
            if (m_CurrentSession)
            {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
            }
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char * name) : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::steady_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::steady_clock::now();

            long long start
                = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            auto highResStart = floatms { m_StartTimepoint.time_since_epoch() };
            auto elapsedTime
                = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                  - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

            Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

            m_Stopped = true;
        }

    private:
        const char * m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };

} // namespace OE

#ifdef PROFILING_ENABLED
#define OE_START_PROFILER(name, path) ::OE::Instrumentor::Get().StartSession(name, path)
#define OE_STOP_PROFILER()            ::OE::Instrumentor::Get().StopSession()
#define OE_PROFILE_SCOPE(name)        ::OE::InstrumentationTimer timer##__LINE__(name);
#define OE_PROFILE_FUNCTION()         OE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define OE_START_PROFILER(name, path)
#define OE_STOP_PROFILER()
#define OE_PROFILE_SCOPE(name)
#define OE_PROFILE_FUNCTION()
#endif
