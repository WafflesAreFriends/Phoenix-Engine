#pragma once

#ifdef PHX_PLATFORM_WINDOWS
#if PHX_DYNAMIC_LINK // If ever change to use dynamic linking
	#ifdef PHX_BUILD_DLL
		#define PHX_API __declspec(dllexport)
	#else
		#define PHX_API __declspec(dllimport)
	#endif
#else
	#define PHX_API
#endif
#else
	#error Phoenix only supports Windows.
#endif

#ifdef HZ_DEBUG
	#define PHX_ENABLE_ASSERTS
#endif

#ifdef PHX_ENABLE_ASSERTS
	#define PHX_ASSERT(x, ...) {if (!(x)) { PHX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } };
	#define PHX_CORE_ASSERT(x, ...) {if(!(x)) {PHX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PHX_ASSERT(x, ...)
	#define PHX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace Phoenix {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}