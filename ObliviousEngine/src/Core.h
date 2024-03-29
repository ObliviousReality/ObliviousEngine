#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define PLATFORM_WINDOWS
	#else
		#error "x86 IS NOT SUPPORTED"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulator NOT SUPPORTED"
	#elif TARGET_OS_IPHONE == 1
		#define PLATFORM_IOS
		#error "IOS NOT SUPPORTED"
	#elif TARGET_OS_MAC == 1
		#define PLATFORM_MACOS
		#error "MacOS NOT SUPPORTED"
	#else
		#error "UNKNOWN APPLE PLATFORM (AND ALSO NOT SUPPORTED)"
		#endif
#elif defined(__ANDROID__)
	#define PLATFORM_ANDROID
	#error "ANDROID NOT SUPPORTED"
#elif defined(__linux__)
	#define PLATFORM_LINUX
	#error "LINUX NOT SUPPORTED"
#else
	#error "UNKNOWN PLATFORM (AND ALSO NOT SUPPORTED)"
#endif

#ifdef OE_DEBUG
	#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
#define ASSERT(x, ...)                                               \
    {                                                                \
        if (!(x))                                                    \
        {                                                            \
            FATAL("APPLICATION ASSERTION FAILED: {0}", __VA_ARGS__); \
            __debugbreak();                                          \
        }                                                            \
    }
#define CORE_ASSERT(x, ...)                                          \
    {                                                                \
        if (!(x))                                                    \
        {                                                            \
            CORE_FATAL("ENGINE ASSERTION FAILED: {0}", __VA_ARGS__); \
            __debugbreak();                                          \
        }                                                            \
    }
#else
#define ASSERT(x, ...)                                               \
    {                                                                \
        if (!(x))                                                    \
        {                                                            \
            FATAL("APPLICATION ASSERTION FAILED: {0}", __VA_ARGS__); \
        }                                                            \
    }
#define CORE_ASSERT(x, ...)                                          \
    {                                                                \
        if (!(x))                                                    \
        {                                                            \
            CORE_FATAL("ENGINE ASSERTION FAILED: {0}", __VA_ARGS__); \
        }                                                            \
    }
#endif // ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

namespace OE
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
