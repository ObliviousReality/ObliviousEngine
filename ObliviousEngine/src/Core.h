#pragma once

#include <memory>

#ifdef OE_PLATFORM_WINDOWS
#if OE_DYNAMIC_LINK
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

#ifdef OE_DEBUG
	#define OE_ENABLE_ASSERTS
#endif

#ifdef OE_ENABLE_ASSERTS
#define OE_ASSERT(x, ...) {if (!(x)) {OE_ERROR("Assertion Failed :(: {0}", __VA_ARGS__); __debugbreak();}}
#define OE_CORE_ASSERT(x, ...) {if (!(x)) {OE_CORE_ERROR("Assertion Failed :(: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define OE_ASSERT(x, ...)
#define OE_CORE_ASSERT(x, ...)
#endif // OE_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define OE_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

namespace OE
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}