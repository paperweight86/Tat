#include "stdafx.h"

#ifdef TAT_WINDOWS

#include "dynamic_libs.h"
#include "str.h"
#include "log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef min
#undef max

uti::ptr TAT_DEF uti::load_library(cstr lib_path)
{
	return(ptr)LoadLibraryA(lib_path);
}

void TAT_DEF uti::unload_library(uti::ptr handle)
{
	FreeLibrary((HMODULE)handle);
}

bool TAT_DEF uti::get_path_library(uti::ptr handle, char* dest, int dest_len)
{
	if(!dest)
		return false;

	if(!dest_len)
		return false;

	if (GetModuleFileNameA((HMODULE)handle, dest, dest_len) == 0)
		return false;

	return true;
}

#endif // TAT_LINUX