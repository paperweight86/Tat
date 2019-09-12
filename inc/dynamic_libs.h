#pragma once

#include "types.h"

namespace uti
{
	ptr  TAT_DEF load_library(cstr lib_path);
	void TAT_DEF unload_library(ptr handle);
	bool TAT_DEF get_path_library(uti::ptr handle, char* dest, int dest_len);
}
