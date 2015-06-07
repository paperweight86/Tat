#include "stdafx.h"
#include "Logger.h"

#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace uti;

const int uti::log::g_iMaxMsg = 1024;

tstr g_Info = _T("Info");
tstr g_InfoShort = _T("Inf");
tstr g_Warning = _T("Warning");
tstr g_WarningShort = _T("Wrn");
tstr g_Error = _T("Error");
tstr g_ErrorShort = _T("Err");
tstr g_Debug = _T("Debug");
tstr g_DebugShort = _T("Dbg");

CLogger* CLogger::m_pInstance = 0;

tstr log::LevelToStr( eLogLevel level, bool _short )
{
	switch( level )
	{
	case Info:
		return _short? g_InfoShort: g_Info;
		break;
	case Warning:
		return _short? g_WarningShort: g_Warning;
		break;
	case Error:
		return _short? g_ErrorShort: g_Error;
		break;
	case Debug:
		return _short? g_DebugShort: g_Debug;
		break;
	default:
		return _short? _T("???"): _T("Unknown");
	}
}

CLogger::CLogger( )
{
	m_eLevel	 = log::Info;
	m_bPrintFullStack = false;
}

CLogger::~CLogger( )
{
	while(!m_ComponentStack.empty())
		m_ComponentStack.pop();
}

CLogger* CLogger::GetInstance( )
{
	if( m_pInstance == NULL )
	{
		m_pInstance = new CLogger();
		return m_pInstance;
	}
	else
	{
		return m_pInstance;
	}
}

void CLogger::DestroyInstance( )
{
	delete m_pInstance;
}

void CLogger::SetLevel( log::eLogLevel level )
{
	m_eLevel = level;
}

void CLogger::PushComponent( tstr component )
{
	m_ComponentStack.push( component );
}

void CLogger::PopComponent( )
{
	m_ComponentStack.pop();
}

tstr CLogger::PeekComponent( )
{
	return m_ComponentStack.top( );
}

log::eLogLevel CLogger::GetLevel( )
{
	return log::Info;
}

tstr CLogger::GetComponent( )
{
	return m_ComponentStack.top();
}

void CLogger::Log( log::eLogLevel level, tstr format, va_list args )
{
	assert( _tclen( format ) <= log::g_iMaxMsg );
	tchar buffer [log::g_iMaxMsg];
	for( int i = 0; i < log::g_iMaxMsg; ++i ) { buffer[i] = 0; }
	tstr levelStr = LevelToStr(level);
	if( !m_ComponentStack.empty() && m_ComponentStack.top() )
	{
		if( !m_bPrintFullStack )
		{
			tstr finalFormat = _T("[%s][%s] %s\n");
			assert( _tclen(levelStr) + _tclen(m_ComponentStack.top()) + _tclen(format) + _tclen(finalFormat) <= log::g_iMaxMsg );
			_stprintf_s<log::g_iMaxMsg>( buffer, finalFormat, m_ComponentStack.top(), levelStr, format );
		}
		else
		{
			tstr finalFormat = _T("[%s]%s");
			std::stack<tstr> tempStack = m_ComponentStack;
			while( !tempStack.empty() )
			{
				tchar tmpBuffer [log::g_iMaxMsg];
				for( int i = 0; i < log::g_iMaxMsg; ++i ) { tmpBuffer[i] = 0; }
				_tcscpy_s<log::g_iMaxMsg>( tmpBuffer, buffer );
				_stprintf_s<log::g_iMaxMsg>( buffer, finalFormat, tempStack.top(), tmpBuffer );
				tempStack.pop();
			}
			finalFormat = _T("%s[%s] %s\n");
			//assert( strlen(levelStr) + strlen(m_ComponentStack.top()) + strlen(format) + strlen(finalFormat) <= log::g_iMaxMsg );
			_stprintf_s<log::g_iMaxMsg>( buffer, finalFormat, buffer, levelStr, format );
		}
	}
	else
	{
		tstr finalFormat = _T("[%s] %s\n");
		assert( _tclen(levelStr) + _tclen(format) + _tclen(finalFormat) <= log::g_iMaxMsg );
		_stprintf_s<log::g_iMaxMsg>( buffer, finalFormat, levelStr, format );
	}
	_vtprintf_s(buffer, args);
}

void CLogger::Log( log::eLogLevel level, tstr format, ... )
{
	va_list args;
	va_start( args, format );
	Log( m_eLevel, format, args );
	va_end( args );
}

void CLogger::Log( tstr format, ... )
{
	va_list args;
	va_start( args, format );
	Log( m_eLevel, format, args );
	va_end( args );
}

void CLogger::Error( tstr format, ... )
{
#ifdef _WIN32
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);
	if(con)
		SetConsoleTextAttribute( con, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
#endif
	va_list args;
	va_start( args, format );
	Log( log::Error, format, args );
	va_end( args );
#ifdef _WIN32
	if(con)
		SetConsoleTextAttribute( con, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
#endif
}

void CLogger::Warning( tstr format, ... )
{
#ifdef _WIN32
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);
	if(con)
		SetConsoleTextAttribute( con, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
#endif
	va_list args;
	va_start( args, format );
	Log( log::Warning, format, args );
	va_end( args );
#ifdef _WIN32
	if(con)
		SetConsoleTextAttribute( con, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
#endif
}

void CLogger::Info( tstr format, ... )
{
	va_list args;
	va_start( args, format );
	Log( log::Info, format, args );
	va_end( args );
}

