#include "stdafx.h"
#include "window.h"

#ifdef TAT_WINDOWS
#include <windows.h>
#include <windowsx.h>
#undef max
#undef min

using namespace uti;

namespace
{
	ptr window_process_message(window* win, uint32 message, uint64 wParam, uint64 lParam)
	{
		int16 wheelDelta = 0;
		bool keyDown = true;
		switch (message)
		{
		case WM_CHAR:
			if (win->text_input_callback)
			{
				win->text_input_callback(wParam);
			}
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			keyDown = false;
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			if (win->keyboard_callback)
			{
				win->keyboard_callback(wParam, keyDown, false);
			}
			break;
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			if (win->mouse_callback)
			{
				// Decode parameters
				bool lButton = (wParam & MK_LBUTTON) == MK_LBUTTON;
				bool mButton = (wParam & MK_MBUTTON) == MK_MBUTTON;
				bool rButton = (wParam & MK_RBUTTON) == MK_RBUTTON;
				int16 xPos = GET_X_LPARAM(lParam);
				int16 yPos = GET_Y_LPARAM(lParam);
				// Fire Callback
				win->mouse_callback(xPos, yPos, lButton, mButton, rButton, 0, win);
				return 0;
			}
			break;
		case WM_MOUSEWHEEL:
			if (win->mouse_callback)
			{
				wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
				// Decode parameters
				bool lButton = (LOWORD(wParam) & MK_LBUTTON) == MK_LBUTTON;
				bool mButton = (LOWORD(wParam) & MK_MBUTTON) == MK_MBUTTON;
				bool rButton = (LOWORD(wParam) & MK_RBUTTON) == MK_RBUTTON;
				POINT pt;
				pt.x = GET_X_LPARAM(lParam);
				pt.y = GET_Y_LPARAM(lParam);
				ScreenToClient((HWND)win->hwnd, &pt);
				// Fire Callback
				win->mouse_callback((i16)pt.x, (i16)pt.y, lButton, mButton, rButton, (float)wheelDelta / (float)WHEEL_DELTA, win);
				return 0;
			}
			break;
		case WM_DROPFILES:
			if(win->drop_file_callback)
			{
				HDROP hDrop = (HDROP)wParam;
				UINT num_files = DragQueryFile(hDrop, UINT_MAX, NULL, 0);
				char* files = new char[num_files*MAX_PATH];
				for (UINT i = 0; i < num_files; ++i)
				{
					DragQueryFile(hDrop, i, files + i*MAX_PATH, MAX_PATH);
				}
				POINT pt = {};
				DragQueryPoint(hDrop, &pt);
				float2 f2pt = { (float)pt.x / (float)uti::window_width(win),
								(float)pt.y / (float)uti::window_height(win) };
				win->drop_file_callback(files, num_files, MAX_PATH, f2pt);
				DragFinish(hDrop);
				delete[] files;
			}
			break;
		}

		return u64_max;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_NCCREATE || message == WM_CREATE)
			return DefWindowProc(hWnd, message, wParam, lParam);

		PAINTSTRUCT ps;
		HDC hdc;

		window* win = (window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		switch (message)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			if (win != NULL)
			{
				auto res = (LRESULT)window_process_message(win, message, wParam, lParam);
				if (res == 0)
					return res;
			}
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

bool uti::window_initialise(window* win, int16 width, int16 height, bool show, tstr windowTitle)
{
	sprintf_s<32>(win->class_name, "%s", "tat_window_windows");
	win->quit = false;
	win->hwnd = 0;

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = 0;//LoadIcon( hInstance, ( LPCTSTR )IDI_... );
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = win->class_name;
	wcex.hIconSm = 0;//LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_... );
	if (!RegisterClassEx(&wcex))
		return false;

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	win->hwnd = (ptr)CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES, win->class_name, windowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, wcex.hInstance,
		NULL);

	// Allows us to access "this" in the message function
	SetWindowLongPtr((HWND)win->hwnd, GWLP_USERDATA, (LONG_PTR)win);

	if (!win->hwnd)
		return false;

	if (show)
		window_show(win);

	return true;
}

bool uti::window_update(window* win)
{
	MSG msg = { 0 };
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			win->quit = true;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void uti::window_show(window* win)
{
	ShowWindow((HWND)win->hwnd, SW_SHOWDEFAULT);
}

void uti::window_close(window* win)
{
	CloseWindow((HWND)win->hwnd);
}

int16 uti::window_width(window* win)
{
	RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	if (GetClientRect((HWND)win->hwnd, &rect))
		return (int16)(rect.right - rect.left);
	else
		return -1;
}

int16 uti::window_height(window* win)
{
	RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	if (GetClientRect((HWND)win->hwnd, &rect))
		return (int16)(rect.bottom - rect.top);
	else
		return -1;
}

void uti::window_get_mouse_pos(int16& x, int16& y)
{
	POINT pt = {};
	if (GetCursorPos(&pt))
	{
		x = (int16)pt.x;
		y = (int16)pt.y;
	}
}

void uti::window_set_cursor_visible(bool visible)
{
	if (visible)
	{
		while (ShowCursor(true) < 0) { _mm_pause(); }
	}
	else
	{
		while (ShowCursor(false) >= 0) { _mm_pause(); }
	}
}

void uti::window_destroy(window* win)
{
	DestroyWindow((HWND)win->hwnd);
}

#endif