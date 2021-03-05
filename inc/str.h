#pragma once

#include "types.h"

#include "rearray.h"
#include "static_array.h"

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

		string(const char* str, i64 len)
		{
			data.allocate_count(len + 1, /*zero*/ true);
			memcpy(data.data, str, len);
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

		i64 length() const const { return data.count-1; }
		char* raw() { return (char*)data.data; }
		const char* raw() const { return (const char*)data.data; }
		void zero() { memset(raw(), 0, length()*sizeof(char)); }
	};

	template <uti::i64 capacity>
	struct fixed_string
	{
		static_array<char, capacity> data;

		fixed_string(const char* str)
		{
			i64 str_len = strnlen(str, capacity);
			memcpy(data.data, str, str_len);
		}

		fixed_string(const uti::string& other)
		{
			data = other.data;
		}

		operator const char*()
		{
			return (const char*)data.data;
		}

		operator string()
		{
			return string((const char*)&data.data[0]);
		}

		i64 length() const { return strnlen(data.data, capacity); }
		char* raw() { return (char*)&data.data[0]; }
		const char* raw() const { return (const char*)&data.data[0]; }
		void zero() { memset(raw(), 0, length() * sizeof(char)); }
	};

	struct string_view
	{
		const char* viewing;
		i64			len;

		string_view(const string& str, i64 offset) : viewing((const char*)str.data.data+offset), len(str.length() - offset)
		{
			assert(offset < str.length() && offset >= 0);
		}

		operator const char*()
		{
			return viewing;
		}

		i64 length() const { return len; }
		const char* raw() const { return viewing; }

		/* TODO: we need to trim the string
		operator string()
		{
		}*/
	};

	template <class string_type>
	uti::i64 find_in_string(const string_type& in, const string& find, bool return_begin = true)
	//uti::i64 uti::find_in_string(uti::string& in, uti::string& find, bool return_begin)
	{
		if (find.length() > in.length())
			return UTI_STR_FIND_NOT_FOUND;

		i64 pos = str::find_char(in.raw(), find.data[0], find.length());

		while (pos != UTI_STR_FIND_NOT_FOUND && pos < in.length() - find.length())
		{
			if (pos == UTI_STR_FIND_NOT_FOUND)
				return UTI_STR_FIND_NOT_FOUND;

			if (memcmp(in.raw() + pos, find.raw(), find.length()) == 0)
				return return_begin ? pos : pos + find.length();

			pos = str::find_char(in.raw(), find.data[0], find.length());
		}

		return UTI_STR_FIND_NOT_FOUND;
	}
}

inline uti::string_view operator+(const uti::string& str, uti::i64 offset)
{
	return uti::string_view(str, offset);
}

namespace str
{
	TAT_DEF uti::i64 strOffToNextFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF char* strOffToNextFloatPtr(char* c, uti::i64 l = 32);

	TAT_DEF uti::i64 strOffToEndFloat(uti::tstr c, uti::i64 l = 32);

	TAT_DEF char* strOffToEndFloatPtr(char* c, uti::i64 l = 32);

	TAT_DEF char*	 find_integer_ptr(char* str, uti::i64 str_len);

	TAT_DEF uti::i64 find_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF char*	 find_char_ptr(char* src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_not_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_last_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_num_char(uti::cstr src, char ch, uti::i64 str_len);

	TAT_DEF uti::i64 find_any_char(uti::cstr src, uti::cstr chars, uti::i64 str_len);

	TAT_DEF uti::i64 find_word(uti::cstr find, uti::i64 find_len, char* src, uti::i64 str_len);

	TAT_DEF uti::i64 find_number(uti::tstr str, uti::i64 str_len);

	TAT_DEF uti::i64 find_end_number(uti::tstr str, uti::i64 str_len);

	TAT_DEF void 	 to_lower_inplace(uti::mstr str, uti::i64 str_len);

	TAT_DEF bool	 string_to_float(char* str, uti::i64 len, float* out_float, char** out_str_after);

	TAT_DEF bool	 string_to_u32(char* str, uti::i64 len, uti::u32* out_u64, char** out_str_after);

	TAT_DEF bool	 read_floats(char* str, uti::i64 len, float* out_float, uti::i64 num_out_float, char** out_ptr);

	TAT_DEF uti::i64 read_any_floats(char* str, uti::i64 len, float* out_float, uti::i64 max_floats, char** out_ptr);

	TAT_DEF uti::i64 read_any_u32(char* str, uti::i64 len, uti::u32* out_integer, uti::i64 max_integers, char** out_ptr);
}