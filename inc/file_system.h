#pragma once

#include "types.h"

namespace uti
{
	void TAT_DEF get_executable_path(tchar* str, size_t strLen);
	void TAT_DEF get_executable_path_w(wchar_t* str, size_t strLen);
	void TAT_DEF get_executable_folder_path(tchar* str, size_t strLen);
	void TAT_DEF get_executable_folder_path_w(wchar_t* str, size_t strLen);

	bool TAT_DEF file_exists(const char* name);

	bool TAT_DEF update_file_mod_time(const char* filepath, uti::u64* update_time);
	bool TAT_DEF file_load_all_lines(const char* filepath, char** out_lines, uti::u64* out_file_len);
}
