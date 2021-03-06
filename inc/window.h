#pragma once

#include <functional>

namespace uti
{
	struct window
	{
		bool	   quit;
		uti::ptr   hwnd;
		char	   class_name[32];
		void(*mouse_callback)(
			uti::int16 /*x*/,
			uti::int16 /*y*/,
			bool /*right down*/,
			bool /*middle down*/,
			bool /*left down*/,
			float /*wheel delta*/,
			window* win);
		void(*keyboard_callback)(
			uti::uint64 /*keycode*/,
			bool /*down*/,
			bool /*syskey*/
			);
		void(*drop_file_callback)(
			uti::mstr files,
			uti::u32 num_files,
			uti::u32 stride,
			uti::float2 pos
			);
		void(*text_input_callback)(
			uti::uint64 character
			);
	};

	TAT_DEF bool	window_initialise(window* win, int16 width, int16 height, bool show, tstr windowTitle = "Main");
	TAT_DEF bool	window_update(window* win);
	TAT_DEF void	window_show(window* win);
	TAT_DEF void	window_close(window* win);
	TAT_DEF int16   window_width(window* win);
	TAT_DEF int16   window_height(window* win);
	TAT_DEF void	window_get_mouse_pos(int16& x, int16& y);
	TAT_DEF void	window_set_cursor_visible(bool visible);
	TAT_DEF void	window_destroy(window* win);
}
