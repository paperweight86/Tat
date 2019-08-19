#pragma once

#ifdef LINUX
	#ifdef TAT_LIB
		#define TAT_DEF __attribute__((visibility("default")))
	#else
		#define TAT_DEF
	#endif
#else
	#ifdef TAT_LIB
		#define TAT_DEF __declspec(dllexport)
	#else
		#define TAT_DEF __declspec(dllimport)
	#endif
#endif

