#include "stdafx.h"
#include "WinWindow.h"

#ifdef _WIN32
	#include <windows.h>
	#include <windowsx.h>
#endif

using namespace uti;

CWinWindow::CWinWindow( )
{
	_stprintf_s<32>( m_sWinClassName, _T("%s%i"), _T("CWinWindow"), m_numInstances );
	m_bQuit = false;
	m_callbackMouse = false;
	m_callbackKeyboard = false;
}


CWinWindow::~CWinWindow( )
{
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_NCCREATE || message == WM_CREATE)
		return DefWindowProc(hWnd, message, wParam, lParam);

    PAINTSTRUCT ps;
    HDC hdc;

	CWinWindow* winWindow = (CWinWindow*)GetWindowLong(hWnd, GWLP_USERDATA);

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
			if (winWindow != NULL)
			{
				auto res = (LRESULT)winWindow->ProcessMessage(message, wParam, lParam);
				if (res == 0)
					return res;
			}
			break;

    }

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool CWinWindow::Initialise( int32 width, int32 height, bool show, tstr windowTitle )
{
	ComponentLogFunc();
	// Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = 0;//LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = m_sWinClassName;
    wcex.hIconSm = 0;//LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
	{
		Logger.Log(log::Error, _T("Unable to register window class."));
        return false;
	}

    // Create window
    RECT rc = { 0, 0, width, height };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    m_hWnd = (ptr)CreateWindow( m_sWinClassName, windowTitle, WS_OVERLAPPEDWINDOW | WS_EX_WINDOWEDGE,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, wcex.hInstance,
                           NULL );

	// Pass "this" to the message function
	SetWindowLongPtr((HWND)m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

    if( !m_hWnd )
	{
		Logger.Log(log::Error, _T("Unable to create window."));
        return false;
	}
	
	if( show )
		Show( );

	return true;
}

bool CWinWindow::Update( )
{
	ComponentLogFunc();
	MSG msg = {0};
	while ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	if (msg.message == WM_QUIT)
	{
		Logger.Log(_T("User closed the window."));
		m_bQuit = true;
	}

	return true;
}

void CWinWindow::Show( )
{
	ShowWindow( (HWND)m_hWnd, SW_SHOWDEFAULT );
}

void CWinWindow::Close( )
{
	CloseWindow( (HWND)m_hWnd );
}

int32 CWinWindow::Width()
{
	RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	if (GetClientRect((HWND)m_hWnd, &rect))
		return rect.right - rect.left;
	else
		return -1;
}

int32 CWinWindow::Height()
{
	RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	if (GetClientRect((HWND)m_hWnd, &rect))
		return rect.bottom - rect.top;
	else
		return -1;
}

void CWinWindow::RegisterMouseInput(MouseInputCallback callback)
{
	m_callbackMouse = true;
	m_mouseCallback = callback;
}

void CWinWindow::RegisterKeyboardInput(KeyboardInputCallback callback)
{
	m_callbackKeyboard = true;
	m_keyboardCallback = callback;
}

ptr CWinWindow::ProcessMessage(uint32 message, uint64 wParam, uint64 lParam)
{
	int16 wheelDelta = 0;
	bool keyDown = true;
	switch (message)
	{
	case WM_KEYUP:
		keyDown = false;
	case WM_KEYDOWN:
		if (m_keyboardCallback)
		{
			m_keyboardCallback(wParam, keyDown, false);
		}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		if (m_callbackMouse) 
		{
			// Decode parameters
			bool lButton = (wParam & MK_LBUTTON) == MK_LBUTTON;
			bool mButton = (wParam & MK_MBUTTON) == MK_MBUTTON;
			bool rButton = (wParam & MK_RBUTTON) == MK_RBUTTON;
			int16 xPos = GET_X_LPARAM(lParam);
			int16 yPos = GET_Y_LPARAM(lParam);
			// Fire Callback
			m_mouseCallback(xPos, yPos, lButton, mButton, rButton, 0);
			return 0;
		}
		break;
	case WM_MOUSEWHEEL:
		if (m_callbackMouse)
		{
			wheelDelta = HIWORD(wParam);
			// Decode parameters
			bool lButton = (LOWORD(wParam) & MK_LBUTTON) == MK_LBUTTON;
			bool mButton = (LOWORD(wParam) & MK_MBUTTON) == MK_MBUTTON;
			bool rButton = (LOWORD(wParam) & MK_RBUTTON) == MK_RBUTTON;
			POINT pt;
			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);
			ScreenToClient((HWND)m_hWnd, &pt);
			// Fire Callback
			m_mouseCallback(pt.x, pt.y, lButton, mButton, rButton, wheelDelta / WHEEL_DELTA);
			return 0;
		}
		break;
	}

	return -1;
}


