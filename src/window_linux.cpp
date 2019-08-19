#include "stdafx.h"
#include "window.h"
#include "log.h"

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

    if(show)
    {
    	uti::window_show(win);
    }

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
		uti::log::err_out("arse\r\n");
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
	auto lwin = (linux_window*)win->hwnd;
	XUnmapWindow(lwin->display, lwin->window);
}

int16 uti::window_width(window* win)
{
	unsigned int width = 0;
	auto lwin = (linux_window*)win->hwnd;
	XGetGeometry(lwin->display, lwin->window, 
		nullptr, 
		nullptr,
		nullptr,
		&width,
		nullptr,
		nullptr,
		nullptr);
	return (int16)width;
}

int16 uti::window_height(window* win)
{
	unsigned int height = 0;
	auto lwin = (linux_window*)win->hwnd;
	XGetGeometry(lwin->display, lwin->window, 
		nullptr, 
		nullptr,
		nullptr,
		nullptr,
		&height,
		nullptr,
		nullptr);
	return (int16)height;
}

void uti::window_get_mouse_pos(int16& x, int16& y)
{
	x=-1;
	y=-1;
}

void uti::window_set_cursor_visible(bool visible)
{

}

void uti::window_destroy(window* win)
{
	auto lwin = (linux_window*)win->hwnd;
	XDestroyWindow(lwin->display, lwin->window);	
}

#endif
