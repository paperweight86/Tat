#include "stdafx.h"

#ifdef TAT_LINUX

#include "dynamic_libs.h"

#include <dlfcn.h>

uti::ptr TAT_DEF uti::load_library(cstr lib_path)
{
	return (uti::ptr)dlopen(lib_path, RTLD_LAZY);
}

void TAT_DEF uti::unload_library(uti::ptr handle)
{
	dlclose((void*)handle);
}

#endif // TAT_LINUX