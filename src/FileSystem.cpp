#include "stdafx.h"

#include "FileSystem.h"

// More windows utilities
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <PathCch.h>
#pragma comment(lib, "PathCch.lib")

void TAT_DEF uti::getExecutableFilePath(tchar* str, size_t strLen)
{
	GetModuleFileName(NULL, str, strLen);
}

void TAT_DEF uti::getExecutableFolderPath(tchar* str, size_t strLen)
{
	getExecutableFilePath(str, strLen);
	PathCchRemoveFileSpec(str, strLen);
}
