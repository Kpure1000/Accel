#pragma once

#ifdef AC_PLATFORM_WINDOWS
	#ifdef AC_DYLIB
		#ifdef AC_BUILD_DLL
			#define AC_API __declspec(dllexport)
		#else
			#define AC_API __declspec(dllimport)
		#endif 
	#else  // AC_DYLIB
		#define AC_API 
	#endif // AC_STLIB
#else
#error Accel only support Windows
#endif // AC_PLATFORM_WINDOWS

namespace accel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}