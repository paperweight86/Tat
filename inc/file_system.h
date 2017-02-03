#pragma once

#include "types.h"

namespace uti
{
	void TAT_DEF getExecutableFilePath(tchar* str, size_t strLen);
	void TAT_DEF getExecutableFilePathW(wchar_t* str, size_t strLen);
	void TAT_DEF getExecutableFolderPath(tchar* str, size_t strLen);
	void TAT_DEF getExecutableFolderPathW(wchar_t* str, size_t strLen);

	bool TAT_DEF file_exists(const char* name);
}
