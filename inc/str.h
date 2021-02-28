#pragma once

#include "types.h"

#include "rearray.h"

#define STR_CHAR_IS_NUM(c)								(*(c) >= '0' && *(c) <= '9')
#define STR_CHAR_IS_NEGNUM_START(c, nextOff, len, next) (*(c) == '-' && nextOff < len && STR_CHAR_IS_NUM(next))
#define STR_CHAR_IS_SCIFLT_EXPONENT(c)	 (*(c) == 'e')
#define STR_CHAR_IS_DECIMAL_POINT(c)     (*(c) == '.')

#define UTI_STR_FIND_NOT_FOUND i64_max

#define UTI_STR_WHITESPACE_CHARS " \r\n\t"

namespace uti
{
	struct string
	{
		rearray<char> data;

		string(const char* str)
		{
			i64 str_len = strnlen(str, plt::max_len_path);
			data.allocate_count(str_len + 1, /*zero*/ true);
			memcpy(data.data, str, str_len);
		}

		string(const uti::string& other)
		{
			data = other.data;
		}

		string(i64 length)
		{
			data.allocate_count(length + 1, /*zero*/ true);
		}

		operator const char*()
		{
			return (const char*)data.data;
		}

		i64 length() { return data.count-1; }
		char* raw() { return (char*)data.data; }
		void zero() { memset(raw(), 0, length()*sizeof(char)); }
	};
}

namespace str
{
	TAT_DEF uti::i64 strOffToNextFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF uti::i64 strOffToEndFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF uti::i64 find_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_not_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_last_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_num_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_any_char(uti::cstr src, uti::cstr chars, uti::i64 str_len);

	TAT_DEF uti::i64 find_word(uti::cstr find, uti::i64 find_len, char* src, uti::i64 str_len);

	TAT_DEF uti::i64 find_number(uti::tstr str, uti::i64 str_len);

	TAT_DEF uti::i64 find_end_number(uti::tstr str, uti::i64 str_len);

	TAT_DEF void 	 to_lower_inplace(uti::mstr str, uti::i64 str_len);
}