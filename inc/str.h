#pragma once

#include "types.h"

#define STR_CHAR_IS_NUM(c)								(*(c) >= '0' && *(c) <= '9')
#define STR_CHAR_IS_NEGNUM_START(c, nextOff, len, next) (*(c) == '-' && nextOff < len && STR_CHAR_IS_NUM(next))
#define STR_CHAR_IS_SCIFLT_EXPONENT(c)	 (*(c) == 'e')
#define STR_CHAR_IS_DECIMAL_POINT(c)     (*(c) == '.')

#define UTI_STR_FIND_NOT_FOUND i64_max

namespace str
{
	TAT_DEF uti::i64 strOffToNextFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF uti::i64 strOffToEndFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF uti::i64 find_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_not_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_num_char(uti::cstr src, char ch, uti::i64 str_len);

	//!< Finds a word within a string by assuming it's surrounded by whitespace
	TAT_DEF uti::i64 find_word(uti::cstr find, uti::i64 find_len, char* src, uti::i64 str_len);

	TAT_DEF uti::i64 find_number(uti::tstr str, uti::i64 str_len);

	TAT_DEF uti::i64 find_end_number(uti::tstr str, uti::i64 str_len);
}