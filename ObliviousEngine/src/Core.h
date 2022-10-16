#pragma once

#ifdef OE_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
#ifdef OE_BUILD_DLL
#define OBLIVIOUSENGINE_API __declspec(dllexport)
#else
#define OBLIVIOUSENGINE_API __declspec(dllimport)
#endif // OE_BUILD_DLL
#else
#define OBLIVIOUSENGINE_API
#endif
#else
#error The Oblivious Engine only supports Windows.
#endif // OE_PLATFORM_WINDOWS
