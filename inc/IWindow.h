#pragma once

#include "tat.h"

namespace uti
{
	class TAT_DEF IWindow
	{
	protected:
		static int32 m_numInstances;
	public:
		IWindow( );
		~IWindow( );
		virtual bool Initialise( int32 width, int32 height, bool show, tstr windowTitle = _T("Main") ) = 0;
		virtual bool Update( ) = 0;
		virtual bool ShouldQuit( ) = 0;
		virtual ptr		GetHandle( ) = 0;
		virtual void	Show( ) = 0;
		virtual void	Close( ) = 0;
		virtual int32   Width() = 0;
		virtual int32   Height() = 0;
	};
}
