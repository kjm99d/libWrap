#pragma once

#ifdef _WIN32
	#ifdef _DLL
		#define DLL_EXPORT __declspec(dllexport) 
	#else
		#define DLL_EXPORT __declspec(dllimport) 
	#endif // ifdef _DLL

#else // #ifndef WIN32
		#define DLL_EXPORT 
#endif

