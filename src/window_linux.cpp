#include "stdafx.h"
#include "window.h"

#ifdef TAT_LINUX

#include<X11/Xlib.h>

using namespace uti;

namespace
{
	ptr window_process_message(window* win, uint32 message, uint64 wParam, uint64 lParam)
	{
		//win->keyboard_callback(wParam, keyDown, false);
		//win->mouse_callback(xPos, yPos, lButton, mButton, rButton, 0, win);
		//win->drop_file_callback(files, num_files, MAX_PATH, f2pt);
		return u64_max;
	}
}

bool uti::window_initialise(window* win, int16 width, int16 height, bool show, tstr windowTitle)
{
	

	return false;
}

bool uti::window_update(window* win)
{
	return false;
}

void uti::window_show(window* win)
{
	
}

void uti::window_close(window* win)
{
	
}

int16 uti::window_width(window* win)
{
	return -1;
}

int16 uti::window_height(window* win)
{
	return -1;
}

void uti::window_get_mouse_pos(int16& x, int16& y)
{
	x=-1;
	y=-1;
}

void uti::window_set_cursor_visible(bool visible)
{

}

#endif
