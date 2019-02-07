#include "stdafx.h"

#ifdef TAT_LINUX

#include "file_system.h"

#include "unistd.h"

void TAT_DEF uti::get_executable_path(tchar* str, size_t strLen)
{
	readlink("/proc/self/exe", str, strLen-1);
}

void TAT_DEF uti::get_executable_path_w(wchar_t* str, size_t strLen)
{
	// errrrrrr?
}

void TAT_DEF uti::get_executable_folder_path(tchar* str, size_t strLen)
{

}

void TAT_DEF uti::get_executable_folder_path_w(wchar_t* str, size_t strLen)
{

}

bool uti::file_exists(const char* name)
{
	FILE* file = fopen(name, "r");
	if (file == nullptr)
	{
		fclose(file);
		return true;
	}
	else 
	{
		return false;
	}
}

bool uti::update_file_mod_time(const char* filepath, uti::u64* update_time)
{
//	HANDLE file_handle;
//	FILETIME mod_time;
//	file_handle = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (file_handle == INVALID_HANDLE_VALUE)
//	{
//		return false;
//	}
//
//	if (!GetFileTime(file_handle, NULL, NULL, &mod_time))
//	{
//		CloseHandle(file_handle);
//		return false;
//	}
//
//	CloseHandle(file_handle);
//
//	u64 mod_time_64 = (u64)mod_time.dwLowDateTime | ((u64)mod_time.dwHighDateTime << 32);
//
//	bool changed = false;
//	if (mod_time_64 > *update_time)
//		changed = true;
//
//	*update_time = mod_time_64;
//
//	return changed;

	return false;
}

bool uti::file_load_all_lines(const char* filepath, char** out_lines, uti::u64* out_file_len)
{
	FILE* ptr_file = fopen(filepath, "r");
	if (ptr_file == nullptr)
		return false;

	fseek(ptr_file, 0, SEEK_END);
	*out_file_len = ftell(ptr_file);
	fseek(ptr_file, 0, SEEK_SET);

	*out_lines = new char[*out_file_len + 1];
	(*out_lines)[*out_file_len] = 0;

	fread(*out_lines, *out_file_len, 1, ptr_file);

	fclose(ptr_file);

	// TODO: This should check the result of the fread_s which was acting odd when I wrote this
	return true;
}

#endif
