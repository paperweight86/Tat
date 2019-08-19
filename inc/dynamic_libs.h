#pragma once

#include "types.h"

namespace uti
{
	ptr  TAT_DEF load_library(cstr lib_path);
	void TAT_DEF unload_library(ptr handle);
}
