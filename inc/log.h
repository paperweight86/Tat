#pragma once

#include "rearray.h"

#define MAX_UTI_LOG_PATH 256
#define MAX_UTI_LOG_STACK 10
#define MAX_UTI_LOG_STACK_ITEM 32


/*  TODO:
	- use "default" logger for no state (singleton?!)
	- log to file
	- thread safe
*/

namespace uti
{
namespace log
{
	TAT_DEF extern const int g_iMaxMsg;
	enum log_level
	{
		level_info = 0,
		level_warning,
		level_error,
		level_debug
	};
	TAT_DEF tstr level_to_str(log_level level, bool _short = false);

	enum log_flag : u32
	{
		flag_none      = 0x00000000,
		// Limits a line to appear only once in output
		flag_once_only = 0x00000001,
	};

	struct TAT_DEF log_config
	{
		bool no_write_console;

		bool write_file;
		char file_path[MAX_UTI_LOG_PATH];

		//bool use_stack;
	};

	struct TAT_DEF log_state
	{
		log_config config;

		ptr file_handle;
		//char stack[MAX_UTI_LOG_STACK][MAX_UTI_LOG_STACK_ITEM];
		uti::rearray<uti::u32> ignore_lines;

		uti::cstr prefix;
	};

	struct TAT_DEF log_prefix_scope
	{
		cstr backup_prefix;
		log_state* m_state;
		log_prefix_scope(log_state* state, cstr prefix) 
		{ 
			m_state = state; 
			backup_prefix = m_state->prefix;
			m_state->prefix = prefix; 
		}
		~log_prefix_scope() 
		{
			m_state->prefix = backup_prefix;
		}
	};

	TAT_DEF void	   init(log_state* state, log_config* config);
	TAT_DEF log_state* get_default_log_state();

	TAT_DEF void out(log_state* state, log_level level, log_flag flags, cstr format, va_list args);
	TAT_DEF void inf_out(cstr format, ...);
	//TAT_DEF void inf_out(log_state* state, cstr string, ...);
	TAT_DEF void err_out(cstr format, ...);
	//TAT_DEF void err_out(log_state* state, cstr string, ...);
	TAT_DEF void wrn_out(cstr format, ...);
	TAT_DEF void wrn_out(log_flag flags, cstr format, ...);
	//TAT_DEF void wrn_out(log_state* state, cstr string, ...);
	TAT_DEF void dbg_out(cstr format, ...);
	//TAT_DEF void dbg_out(log_state* state, cstr string, ...);

	TAT_DEF void set_prefix(log_state* state, cstr prefix);

	#define MACRO_STR_CONCAT_NO_EXP(A, B) A ## B
	#define MACRO_STR_CONCAT(A, B) MACRO_STR_CONCAT_NO_EXP(A,B)
	#define UTI_LOG_PREFIX_SCOPE_(state, prefix) uti::log::log_prefix_scope MACRO_STR_CONCAT(_scoped_log_prefix,__COUNT__) (state, prefix)
	#define UTI_LOG_PREFIX_SCOPE(prefix) UTI_LOG_PREFIX_SCOPE_(uti::log::get_default_log_state(), prefix)
	#define UTI_LOG_PREFIX_SCOPE_FUNC() UTI_LOG_PREFIX_SCOPE(__FUNCTION__)
}
}
