#pragma once

#include "types.h"

#define STR_CHAR_IS_NUM(c)								(*(c) >= '0' && *(c) <= '9')
#define STR_CHAR_IS_NEGNUM_START(c, nextOff, len, next) (*(c) == '-' && nextOff < len && STR_CHAR_IS_NUM(next))
#define STR_CHAR_IS_SCIFLT_EXPONENT(c)	 (*(c) == 'e')
#define STR_CHAR_IS_DECIMAL_POINT(c)     (*(c) == '.')

namespace str
{
	size_t strOffToNextFloat(uti::tstr c)
	{
		size_t off = 0;
		size_t len = strlen(c);
		bool lastWasNum = STR_CHAR_IS_NUM(c + off);

		while (    !STR_CHAR_IS_NUM(c + off)
				&& !STR_CHAR_IS_NEGNUM_START(c + off, off + 1, len, c + off + 1)
			    && off < len)
		{
			lastWasNum = STR_CHAR_IS_NUM(c + off);
			++off;
		}

		return off;
	}

	size_t strOffToEndFloat(uti::tstr c)
	{
		size_t off = 0;
		size_t len = strlen(c);
		bool lastWasNum = STR_CHAR_IS_NUM(c + off);

		while ( (    STR_CHAR_IS_NUM(c + off) 
				  || STR_CHAR_IS_DECIMAL_POINT(c + off)
			      || (STR_CHAR_IS_NEGNUM_START(c + off, off + 1, len, c + off + 1) && off == 0)
				  || (lastWasNum && STR_CHAR_IS_SCIFLT_EXPONENT(c + off)) )
				&& off < len)
		{
			lastWasNum = STR_CHAR_IS_NUM(c + off);
			++off;
		}

		return off;
	}
}
