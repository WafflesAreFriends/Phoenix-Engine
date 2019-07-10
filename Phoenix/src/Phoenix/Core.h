#pragma once

#ifdef PHX_PLATFORM_WINDOWS
	#ifdef PHX_BUILD_DLL
		#define PHX_API __declspec(dllexport)
	#else
		#define PHX_API __declspec(dllimport)
	#endif
#else
	#error Phoenix only supports Windows.
#endif

#define BIT(x) (1 << x)