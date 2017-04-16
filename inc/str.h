#pragma once

#include "types.h"

#define STR_CHAR_IS_NUM(c)								(*(c) >= '0' && *(c) <= '9')
#define STR_CHAR_IS_NEGNUM_START(c, nextOff, len, next) (*(c) == '-' && nextOff < len && STR_CHAR_IS_NUM(next))
#define STR_CHAR_IS_SCIFLT_EXPONENT(c)	 (*(c) == 'e')
#define STR_CHAR_IS_DECIMAL_POINT(c)     (*(c) == '.')

#define UTI_STR_FIND_NOT_FOUND _CRT_SIZE_MAX

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

	size_t find_char(uti::cstr src, char ch, size_t str_len)
	{
		for (size_t i = 0; i < str_len; i++)
		{
			if (src[i] == ch)
				return i;
		}

		return UTI_STR_FIND_NOT_FOUND;
	}

	size_t find_not_char(uti::cstr src, char ch, size_t str_len)
	{
		for (size_t i = 0; i < str_len; i++)
		{
			if (src[i] != ch)
				return i;
		}

		return UTI_STR_FIND_NOT_FOUND;
	}

	uti::u64 find_num_char(uti::cstr src, char ch, uti::u64 str_len)
	{
		for (uti::u64 i = 0; i < str_len; i++)
		{
			if (src[i] != ch)
				return i;
		}

		return u64_max;
	}

	//!< Finds a word within a string by assuming it's surrounded by whitespace
	uti::u64 find_word(uti::cstr find, uti::u64 find_len, char* src, uti::u64 str_len)
	{
		if (str_len < find_len)
			return u64_max;

		const uti::u64 buffer_size = 256;
//		char buff[buffer_size] = {};
//		uti::u64 buffer_usage = find_len + 2;
		char* cur_str = src;
//		uti::u64 cur_offset = 0;
		for (uti::u64 i = 0; i < str_len; i++)
		{
			// TODO: [DanJ] Slide a window through the file looking for the string surrounded by whitespace
			if (strncmp(cur_str + i,find,find_len) == 0)
			{
				return i;
			}
		}

		return u64_max;
	}
}
