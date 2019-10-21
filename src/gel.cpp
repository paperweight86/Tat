#include <stdafx.h>

#include "gel.h"

#ifdef TAT_WINDOWS

using namespace uti;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <GL/gl.h>

ptr gel::create_gl_context(ptr hwnd)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC hdc = GetDC((HWND)hwnd);

	int  pxFmt = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pxFmt, &pfd);

	return (ptr)wglCreateContext(hdc);
}

bool gel::set_gl_context(ptr hwnd, ptr gl_context)
{
	HDC hdc = GetDC((HWND)hwnd);
	return wglMakeCurrent(hdc, (HGLRC)gl_context) != GL_FALSE;
}

void gel::swap_gl_buffers(ptr hdc, ptr gl_context)
{
	SwapBuffers((HDC)hdc);
}

void uti::gel::destroy_gl_context(uti::ptr gl_context, uti::ptr hwnd)
{
	wglDeleteContext((HGLRC)gl_context);
}

#else

#include <GL/glx.h>

#include "window_linux.h"

uti::ptr uti::gel::create_gl_context(uti::ptr hwnd)
{
	auto lwin = (linux_window*)hwnd;
	/*GLint attribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo* visual_info = glXChooseVisual(lwin->display, 0, attribs);
	if(visual_info == NULL)
	{
		return 0;
	}*/

	XWindowAttributes win_att = {};
	XGetWindowAttributes(lwin->display, lwin->window, &win_att);
	XVisualInfo vi_template = {};
	vi_template.visualid = XVisualIDFromVisual(win_att.visual);
	int num_vi_items = 0;
	XVisualInfo* visual_info = XGetVisualInfo(lwin->display, VisualIDMask, &vi_template, &num_vi_items);
	
	GLXContext context = glXCreateContext(lwin->display, visual_info, NULL, GL_TRUE);

	//Window root = DefaultRootWindow(lwin->display);
	//Colormap colormap = XCreateColormap(lwin->display, lwin->window, visual_info->visual, AllocNone);
	//XSetWindowColormap(lwin->display, lwin->window, colormap);

	return (uti::u64)context;
}

bool uti::gel::set_gl_context(uti::ptr hwnd, uti::ptr gl_context)
{
	auto lwin = (linux_window*)hwnd;
	return glXMakeCurrent(lwin->display, lwin->window, (GLXContext)gl_context);
}

void uti::gel::swap_gl_buffers(uti::ptr hdc, uti::ptr hwnd)
{
	auto lwin = (linux_window*)hwnd;
	glXSwapBuffers(lwin->display, lwin->window);
}

void uti::gel::destroy_gl_context(uti::ptr gl_context, uti::ptr hwnd)
{
	auto lwin = (linux_window*)hwnd;
	glXDestroyContext(lwin->display, (GLXContext)gl_context);
}

#endif