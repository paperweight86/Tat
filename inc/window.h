#pragma once

#include <functional>

namespace uti
{
	struct window
	{
		bool	 quit;
		uti::ptr hwnd;
		char	 class_name[32];
		void(*mouse_callback)(
			uti::int16 /*x*/,
			uti::int16 /*y*/,
			bool /*right down*/,
			bool /*middle down*/,
			bool /*left down*/,
			int16 /*wheel delta*/);
		void(*keyboard_callback)(
			uti::uint64 /*keycode*/,
			bool /*down*/,
			bool /*syskey*/
			);
		void(*drop_file_callback)(
			uti::mstr files,
			uti::u32 num_files,
			uti::u32 stride
			);
	};

	TAT_DEF bool	window_initialise(window* win, int32 width, int32 height, bool show, tstr windowTitle = _T("Main"));
	TAT_DEF bool	window_update(window* win);
	TAT_DEF void	window_show(window* win);
	TAT_DEF void	window_close(window* win);
	TAT_DEF int32   window_width(window* win);
	TAT_DEF int32   window_height(window* win);
	TAT_DEF void	window_get_mouse_pos(int16& x, int16& y);
}
