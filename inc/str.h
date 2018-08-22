#pragma once

#include "types.h"

#define STR_CHAR_IS_NUM(c)								(*(c) >= '0' && *(c) <= '9')
#define STR_CHAR_IS_NEGNUM_START(c, nextOff, len, next) (*(c) == '-' && nextOff < len && STR_CHAR_IS_NUM(next))
#define STR_CHAR_IS_SCIFLT_EXPONENT(c)	 (*(c) == 'e')
#define STR_CHAR_IS_DECIMAL_POINT(c)     (*(c) == '.')

#define UTI_STR_FIND_NOT_FOUND _CRT_SIZE_MAX

namespace str
{
	TAT_DEF size_t strOffToNextFloat(uti::tstr c);

	TAT_DEF size_t strOffToEndFloat(uti::tstr c);

	TAT_DEF size_t find_char(uti::cstr src, char ch, size_t str_len);

	TAT_DEF size_t find_not_char(uti::cstr src, char ch, size_t str_len);

	TAT_DEF uti::u64 find_num_char(uti::cstr src, char ch, uti::u64 str_len);

	//!< Finds a word within a string by assuming it's surrounded by whitespace
	TAT_DEF uti::u64 find_word(uti::cstr find, uti::u64 find_len, char* src, uti::u64 str_len);

	TAT_DEF size_t find_number(uti::tstr str, uti::u64 str_len);

	TAT_DEF size_t find_end_number(uti::tstr str, uti::u64 str_len);
}
