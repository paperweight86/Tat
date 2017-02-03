#include "stdafx.h"

#include "file_system.h"

// More windows utilities
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <PathCch.h>
#pragma comment(lib, "PathCch.lib")

void TAT_DEF uti::getExecutableFilePath(tchar* str, size_t strLen)
{
	GetModuleFileName(NULL, str, (DWORD)strLen);
}

void TAT_DEF uti::getExecutableFilePathW(wchar_t* str, size_t strLen)
{
	GetModuleFileNameW(NULL, str, (DWORD)strLen);
}

void TAT_DEF uti::getExecutableFolderPath(tchar* str, size_t strLen)
{
	getExecutableFilePath(str, strLen);
	PathRemoveFileSpec(str);
}

void TAT_DEF uti::getExecutableFolderPathW(wchar_t* str, size_t strLen)
{
	getExecutableFilePathW(str, strLen);
	PathRemoveFileSpecW(str);
}

bool uti::file_exists(const char* name)
{
	FILE* file = NULL;
	if (fopen_s(&file, name, "r") == 0)
	{
		fclose(file);
		return true;
	}
	else 
	{
		return false;
	}
}
