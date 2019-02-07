#include "stdafx.h"
#include "window.h"

#ifdef TAT_LINUX

#include<X11/Xlib.h>

using namespace uti;

struct linux_window
{
	Display* display;
	Window   window;
};

bool uti::window_initialise(window* win, int16 width, int16 height, bool show, tstr windowTitle)
{
	auto lwin = new linux_window;
	memset(lwin, 0, sizeof(linux_window));
	lwin->display = XOpenDisplay(nullptr);
    if (lwin->display == nullptr)
    {
    	delete lwin;
        return false;
    }

    int def_screen = DefaultScreen(lwin->display);

    lwin->window = XCreateSimpleWindow(
    	lwin->display,
    	RootWindow(lwin->display, def_screen),
    	10, 10, 200, 200, 1,
    	BlackPixel(lwin->display, def_screen),
    	WhitePixel(lwin->display, def_screen)
    	);

    XSelectInput(lwin->display, lwin->window,
    	ExposureMask | KeyPressMask | KeyReleaseMask
    	);

    XMapWindow(lwin->display, lwin->window);

    win->hwnd = (uti::ptr)lwin;

	return true;
}

bool uti::window_update(window* win)
{
	auto lwin = (linux_window*)win->hwnd;

	XEvent event;
	while(XCheckMaskEvent(
			lwin->display, 
			ExposureMask | KeyPressMask | KeyReleaseMask, 
			&event
		 ))
	{
		switch(event.type)
		{
			case Expose:

				break;

			case KeyPress:
				if(win->keyboard_callback)
				{
					win->keyboard_callback(event.xkey.keycode, true, false);
				}
				break;

			case KeyRelease:
				if(win->keyboard_callback)
				{
					win->keyboard_callback(event.xkey.keycode, false, false);
				}
				break;
		}
	}

	//win->mouse_callback(xPos, yPos, lButton, mButton, rButton, 0, win);
	//win->drop_file_callback(files, num_files, MAX_PATH, f2pt);

	return false;
}

void uti::window_show(window* win)
{
	auto lwin = (linux_window*)win->hwnd;
	XMapWindow(lwin->display, lwin->window);
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
