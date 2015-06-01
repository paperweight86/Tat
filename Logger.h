#pragma once

#include <stack>

namespace uti
{
	namespace log
	{
		const int g_iMaxMsg = 1024;
		enum eLogLevel
		{
			Info = 0,
			Warning,
			Error,
			Debug
		};
		tstr LevelToStr( eLogLevel level, bool _short = false );
	}

	class CLogger
	{
	private:
		CLogger( );
		static CLogger*	 m_pInstance;
		log::eLogLevel   m_eLevel;
		std::stack<tstr> m_ComponentStack;
		bool     m_bPrintFullStack;
	private:
		void Log( log::eLogLevel level, tstr format, va_list args );
	public:
		~CLogger( );
		static CLogger* GetInstance( );
		static void DestroyInstance( );
		void SetLevel( log::eLogLevel level = log::Info );
		void PushComponent( tstr component = 0 );
		void PopComponent( );
		tstr PeekComponent( );
		log::eLogLevel GetLevel( );
		tstr GetComponent( );
		void Log( log::eLogLevel level, tstr format, ... );
		void Log( tstr format, ... );
		void Error( tstr format, ... );
		void Warning( tstr format, ... );
		void Info( tstr format, ... );
	};

	#define Logger (*CLogger::GetInstance( ))
}