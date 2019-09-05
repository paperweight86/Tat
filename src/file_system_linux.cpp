#include "stdafx.h"

#ifdef TAT_LINUX

#include "file_system.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "unistd.h"

void TAT_DEF uti::get_executable_path(tchar* str, size_t strLen)
{
	readlink("/proc/self/exe", str, strLen-1);
}

void TAT_DEF uti::get_executable_path_w(wchar_t* str, size_t strLen)
{
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
	struct stat result;
	if(stat(filepath, &result) == 0)
	{
	    *update_time = result.st_mtime;
	}

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

bool uti::file_copy(const char* src_file, const char* dst_file)
{
	int src_fd = open(src_file, O_RDONLY);
	struct stat stat_buf;
	fstat(src_fd, &stat_buf);
	int dst_fd = open(dst_file, O_WRONLY | O_CREAT, stat_buf.st_mode);
	off_t offset = 0;
	sendfile(dst_fd, src_fd, &offset, stat_buf.st_size);
	close(src_fd);
	close(dst_fd);

	return true;
}

#endif
