#include "stdafx.h"
#include "window.h"
#include "log.h"

#ifdef TAT_LINUX

#include<X11/Xlib.h>
#include <X11/XKBlib.h>

using namespace uti;

#include "window_linux.h"

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

    int screen = DefaultScreen(lwin->display);

/*    lwin->window = XCreateSimpleWindow(
    	lwin->display,
    	RootWindow(lwin->display, def_screen),
    	0, 0, width, height, 0,
    	BlackPixel(lwin->display, def_screen),
    	WhitePixel(lwin->display, def_screen)
    	);*/

    XSetWindowAttributes swa = {};
    swa.colormap = DefaultColormap(lwin->display, screen);
 	swa.event_mask = ExposureMask | KeyPressMask;
	lwin->window = XCreateWindow(lwin->display, RootWindow(lwin->display, screen), 0, 0, width, height, 0, DefaultDepth(lwin->display, screen), InputOutput, DefaultVisual(lwin->display, screen), CWColormap | CWEventMask, &swa);

    XSelectInput(lwin->display, lwin->window,
    	ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask
    	);

    XStoreName(lwin->display, lwin->window, windowTitle);

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
			ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask, 
			&event
		 ))
	{
 	//while(1) {
        //XNextEvent(lwin->display, &event);
		
		switch(event.type)
		{
			case Expose:

				break;

			case MotionNotify:
				if (win->mouse_callback)
				{
					win->mouse_callback(
						event.xmotion.x /*x*/,
						event.xmotion.y /*y*/,
						event.xmotion.state & Button1Mask,
						event.xmotion.state & Button2Mask,
						event.xmotion.state & Button3Mask,
						0, // TODO: wheel - where from?
						win);
				}
				break;

			case ButtonPress:
			case ButtonRelease:
				if(win->mouse_callback)
				{
					win->mouse_callback(
						event.xmotion.x /*x*/,
						event.xmotion.y /*y*/,
						event.xmotion.state & Button1Mask,
						event.xmotion.state & Button2Mask,
						event.xmotion.state & Button3Mask,
						0, // TODO: wheel - where from?
						win);
				}
				break;

			case KeyPress:
				if(win->keyboard_callback)
				{
					KeySym keysym = XkbKeycodeToKeysym( lwin->display, event.xkey.keycode, 0, event.xkey.state & ShiftMask ? 0 : 1);
					win->keyboard_callback(keysym, true, false);
					//printf("key down %lu!\r\n", keysym);
				}
				break;

			case KeyRelease:
				if(win->keyboard_callback)
				{
					KeySym keysym = XkbKeycodeToKeysym( lwin->display, event.xkey.keycode, 0, event.xkey.state & ShiftMask ? 0 : 1);
					win->keyboard_callback(keysym, false, false);
					//printf("key up %lu!\r\n", keysym);
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
	int an_int = 0;
	unsigned int a_uint = 0;
	Window* root = 0;
	/*XGetGeometry(
		lwin->display, 
		lwin->window, 
		root, 
		&an_int,
		&an_int,
		&width,
		&a_uint,
		&a_uint,
		&a_uint);*/
	return 1000;//(int16)width;
}

int16 uti::window_height(window* win)
{
	unsigned int height = 0;
	auto lwin = (linux_window*)win->hwnd;
	int an_int = 0;
	unsigned int a_uint = 0;
	Window* root = 0;
	/*XGetGeometry(lwin->display, lwin->window, 
		root, 
		&an_int,
		&an_int,
		&a_uint,
		&height,
		&a_uint,
		&a_uint);*/
	return 1000;//(int16)height;
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
