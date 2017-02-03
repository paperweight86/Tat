#pragma once

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
	};

	TAT_DEF void init(log_state* state, log_config* config);
	TAT_DEF void out(log_state* state, log_level level, cstr format, va_list args);
	TAT_DEF void inf_out(cstr format, ...);
	//TAT_DEF void inf_out(log_state* state, cstr string, ...);
	TAT_DEF void err_out(cstr format, ...);
	//TAT_DEF void err_out(log_state* state, cstr string, ...);
	TAT_DEF void wrn_out(cstr format, ...);
	//TAT_DEF void wrn_out(log_state* state, cstr string, ...);
	TAT_DEF void dbg_out(cstr format, ...);
	//TAT_DEF void dbg_out(log_state* state, cstr string, ...);
}
}
