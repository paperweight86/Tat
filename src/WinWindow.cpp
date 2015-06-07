#include "stdafx.h"
#include "WinWindow.h"

#ifdef _WIN32
	#include <windows.h>
#endif

using namespace uti;

CWinWindow::CWinWindow( )
{
	_stprintf_s<32>( m_sWinClassName, _T("%s%i"), _T("CWinWindow"), m_numInstances );
	m_bQuit = false;
}


CWinWindow::~CWinWindow( )
{
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

	if (message > WM_MOUSEFIRST && message < WM_MOUSELAST)
		return 0;

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
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
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
	if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		if( msg.message == WM_QUIT )
		{
			Logger.Log( _T("User closed the window.") );
			m_bQuit = true;
		}
		return true;
	}
	else
	{
		return false;
	}
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


