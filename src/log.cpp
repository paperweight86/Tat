#include "stdafx.h"

#include "log.h"

#include "ext/murmur_hash_3.h"

#include <stdarg.h>

//using namespace uti;

uti::tstr g_Info = _T("Info");
uti::tstr g_InfoShort = _T("Inf");
uti::tstr g_Warning = _T("Warning");
uti::tstr g_WarningShort = _T("Wrn");
uti::tstr g_Error = _T("Error");
uti::tstr g_ErrorShort = _T("Err");
uti::tstr g_Debug = _T("Debug");
uti::tstr g_DebugShort = _T("Dbg");

static uti::log::log_state g_default_logger;

const int uti::log::g_iMaxMsg = 1024;

uti::tstr uti::log::level_to_str(log::log_level level, bool _short)
{
	switch (level)
	{
	case log::level_info:
		return _short ? g_InfoShort : g_Info;
		break;
	case log::level_warning:
		return _short ? g_WarningShort : g_Warning;
		break;
	case log::level_error:
		return _short ? g_ErrorShort : g_Error;
		break;
	case log::level_debug:
		return _short ? g_DebugShort : g_Debug;
		break;
	default:
		return _short ? _T("???") : _T("Unknown");
	}
}

void uti::log::init(log::log_state* state, log::log_config* config)
{
	state->file_handle = NULL;
	state->config = *config;

	if (state->config.write_file)
	{
		FILE* file;
		if (fopen_s(&file, state->config.file_path, "w+") == 0)
		{
			state->file_handle = (ptr)file;
		}
	}

	//memset(state->stack, 0, MAX_UTI_LOG_STACK*MAX_UTI_LOG_STACK_ITEM);
}

void uti::log::out(log_state* state, log_level level, log_flag flags, cstr format, va_list args)
{
	assert(_tclen(format) <= log::g_iMaxMsg);
	tchar buffer[log::g_iMaxMsg];
	memset(buffer, 0, log::g_iMaxMsg);
	tchar fmt_buffer[log::g_iMaxMsg];
	memset(fmt_buffer, 0, log::g_iMaxMsg);
	cstr levelStr = level_to_str(level);
	//if (!m_ComponentStack.empty() && m_ComponentStack.top())
	//{
	//	if (!m_bPrintFullStack)
	//	{
	//		tstr finalFormat = _T("[%s][%s] %s\n");
	//		assert(_tclen(levelStr) + _tclen(m_ComponentStack.top()) + _tclen(format) + _tclen(finalFormat) <= log::g_iMaxMsg);
	//		_stprintf_s<log::g_iMaxMsg>(buffer, finalFormat, m_ComponentStack.top(), levelStr, format);
	//	}
	//	else
	//	{
	//		tstr finalFormat = _T("[%s]%s");
	//		std::stack<tstr> tempStack = m_ComponentStack;
	//		while (!tempStack.empty())
	//		{
	//			tchar tmpBuffer[log::g_iMaxMsg];
	//			for (int i = 0; i < log::g_iMaxMsg; ++i) { tmpBuffer[i] = 0; }
	//			_tcscpy_s<log::g_iMaxMsg>(tmpBuffer, buffer);
	//			_stprintf_s<log::g_iMaxMsg>(buffer, finalFormat, tempStack.top(), tmpBuffer);
	//			tempStack.pop();
	//		}
	//		finalFormat = _T("%s[%s] %s\n");
	//		//assert( strlen(levelStr) + strlen(m_ComponentStack.top()) + strlen(format) + strlen(finalFormat) <= log::g_iMaxMsg );
	//		_stprintf_s<log::g_iMaxMsg>(buffer, finalFormat, buffer, levelStr, format);
	//	}
	//}
	//else
	{
		cstr finalFormat = _T("[%s] %s\n");
		assert(_tclen(levelStr) + _tclen(format) + _tclen(finalFormat) <= log::g_iMaxMsg);
		sprintf_s<log::g_iMaxMsg>(fmt_buffer, finalFormat, levelStr, format);
		vsprintf_s(buffer, log::g_iMaxMsg, fmt_buffer, args);
	}

	if ((flags & flag_once_only) == flag_once_only)
	{
		u32 line_hash = 0;
		MurmurHash3_x86_32(buffer, (int)strnlen(buffer, log::g_iMaxMsg), 0, (void*)&line_hash);
		for (i64 i = 0; i < state->ignore_lines.size; ++i)
		{
			if (state->ignore_lines[i] == line_hash)
				return; // ignore we've printed it before
		}

		// add to ignore list
		state->ignore_lines.add_end(line_hash);
	}

	if(!state->config.no_write_console)
		printf_s(buffer);

	if (state->config.write_file && state->file_handle != NULL)
	{
		fwrite(buffer, strnlen(buffer, log::g_iMaxMsg), 1, (FILE*)state->file_handle);
	}
}

void uti::log::inf_out(cstr format, ...)
{
	va_list args;
	va_start(args, format);
	out(&g_default_logger, level_info, flag_none, format, args);
	va_end(args);
}

//void uti::log::inf_out(log_state* state, cstr format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	out(state, level_info, format, args);
//	va_end(args);
//}

void uti::log::err_out(cstr format, ...)
{
	va_list args;
	va_start(args, format);
	out(&g_default_logger, level_error, flag_none, format, args);
	va_end(args);
}

//void uti::log::err_out(log_state* state, cstr format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	out(state, level_error, format, args);
//	va_end(args);
//}

void uti::log::wrn_out(cstr format, ...)
{
	va_list args;
	va_start(args, format);
	out(&g_default_logger, level_warning, flag_none, format, args);
	va_end(args);
}

void uti::log::wrn_out(log_flag flags, cstr format, ...)
{
	va_list args;
	va_start(args, format);
	out(&g_default_logger, level_warning, flags, format, args);
	va_end(args);
}

//void uti::log::wrn_out(log_state* state, cstr format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	out(state, level_warning, format, args);
//	va_end(args);
//}

void uti::log::dbg_out(cstr format, ...)
{
#ifdef TAT_DEBUG
	va_list args;
	va_start(args, format);
	out(&g_default_logger, level_debug, flag_none, format, args);
	va_end(args);
#endif
}

//void uti::log::dbg_out(log_state* state, cstr format, ...)
//{
//#ifdef TAT_DEBUG
//	va_list args;
//	va_start(args, format);
//	out(state, level_debug, format, args);
//	va_end(args);
//#endif
//}
