#include <stdafx.h>

#include "gel.h"

#include <GL/gl.h>
//#include <gl/GLU.h>

using namespace uti;

#ifdef TAT_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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

void gel::swap_gl_buffers(ptr hdc)
{
	SwapBuffers((HDC)hdc);
}

void gel::destroy_gl_context(ptr gl_context)
{
	wglDeleteContext((HGLRC)gl_context);
}

#else

ptr gel::create_gl_context(ptr hwnd)
{
	return 0;
}

bool gel::set_gl_context(ptr hwnd, ptr gl_context)
{
	return false;
}

void gel::swap_gl_buffers(ptr hdc)
{
	
}

void gel::destroy_gl_context(ptr gl_context)
{
	
}

#endif