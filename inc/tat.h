#pragma once

#ifdef TAT_LIB
	#define TAT_DEF __declspec(dllexport)
#else
	#define TAT_DEF __declspec(dllimport)
#endif

