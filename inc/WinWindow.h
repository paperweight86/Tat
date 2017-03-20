#pragma once

#include "IWindow.h"

#include "tat.h"

#include "Callback.h"

namespace uti
{
	class TAT_DEF CWinWindow : public IWindow
	{
	private:
		bool	 m_bQuit;
		ptr		 m_hWnd;
		tchar	 m_sWinClassName [32];
		mouse_input_callback_sig* m_mouseCallback;
		keyboard_input_callback_sig* m_keyboardCallback;
	public:
		CWinWindow( );
		~CWinWindow( );
		bool Initialise( int32 width, int32 height, bool show, tstr windowTitle = _T("Main") );
		bool Update( );
		bool ShouldQuit( ) { return m_bQuit; }
		ptr	    GetHandle( ) { return m_hWnd; }
		void	Show( );
		void	Close( );
		int32   Width( );
		int32   Height( );
		void	RegisterMouseInput(mouse_input_callback_sig* callback);
		void	RegisterKeyboardInput(keyboard_input_callback_sig* callback);
		void	GetMousePos(int16& x, int16& y);

		ptr ProcessMessage(uint32 message, uint64 wParam, uint64 lParam);
	};

}
