#pragma once

#include "tat.h"

#include <functional>

namespace uti
{
	typedef void mouse_input_callback_sig(
		int16 /*x*/,
		int16 /*y*/,
		bool /*right down*/,
		bool /*middle down*/,
		bool /*left down*/,
		int16 /*wheel delta*/
	);

	typedef void keyboard_input_callback_sig(
		u64 /*keycode*/,
		bool /*down*/,
		bool /*syskey*/
	);

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
		virtual void	RegisterMouseInput(mouse_input_callback_sig* callback) = 0;
		virtual void	RegisterKeyboardInput(keyboard_input_callback_sig* callback) = 0;
	};
}
