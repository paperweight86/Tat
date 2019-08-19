#pragma once

namespace uti
{
namespace gel
{
	TAT_DEF	unsigned long	create_gl_context(unsigned long);
	TAT_DEF	bool		set_gl_context(ptr hwnd, ptr gl_context);
	TAT_DEF	void		swap_gl_buffers(uti::ptr hdc);
	TAT_DEF	void		destroy_gl_context(uti::ptr gl_context);
}
}