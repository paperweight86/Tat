#pragma once

#include "IWindow.h"

#include "tat.h"

namespace uti
{
	class TAT_DEF CWinWindow : public IWindow
	{
	private:
		bool	 m_bQuit;
		ptr		 m_hWnd;
		tchar	 m_sWinClassName [32];
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
	};

}
