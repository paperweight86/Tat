#include "stdafx.h"

#ifdef TAT_LINUX

#include "dynamic_libs.h"
#include "str.h"
#include "log.h"

#include <dlfcn.h>
#include <link.h>

uti::ptr TAT_DEF uti::load_library(cstr lib_path)
{
	return (uti::ptr)dlopen(lib_path, RTLD_NOW);
}

void TAT_DEF uti::unload_library(uti::ptr handle)
{
	dlclose((void*)handle);
}

// TODO: This will not work for address space layout randomization (-pie -fPIE in gcc)
// https://stackoverflow.com/questions/19451791/get-loaded-address-of-a-elf-binary-dlopen-is-not-working-as-expected
bool TAT_DEF uti::get_path_library(uti::ptr handle, char* dest, int dest_len)
{
	if(!dest)
		return false;

	if(!dest_len)
		return false;

	struct link_map* lm = (struct link_map*)handle;

	// Read the maps file for this elf which contains all the loaded dynaimc libs
	FILE* file = fopen("/proc/self/maps", "r");
	//     address           perms offset   dev   inode       pathname
    //	   00400000-00452000 r-xp  00000000 08:02 173521      /usr/bin/dbus-daemon
    const int buffer_size = 256;
    char buffer[buffer_size] = {};
    while(!feof(file))
    {
    	char* data = fgets(&buffer[0], buffer_size, file);
    	if(data != NULL)
    	{
    		int pos = 0;
    		pos += str::find_not_char(data+pos, ' ', buffer_size-pos);
    		int end = str::find_char(data+pos, '-', buffer_size-pos);
    		char* address = data + pos;
    		int address_len = end - pos;
    		address[address_len] = '\0';
    		uti::ptr address_int = strtoul(address, NULL, 16);
    		if(lm->l_addr == address_int)
    		{
    			// Skip over the columns we don't care about
    			for(int i = 0; i < 5; ++i)
    				pos += str::find_char(data+pos, ' ', buffer_size-pos) + 1;
    			pos += str::find_not_char(data+pos, ' ', buffer_size-pos);
    			int len = str::find_any_char(data+pos, UTI_STR_WHITESPACE_CHARS, buffer_size-pos);
    			memcpy(dest, data+pos, dest_len < len? dest_len: len );
    			break;
    		}
    	}
    }
	fclose(file);

	return true;
}

#endif // TAT_LINUX