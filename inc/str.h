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
		TAT_DEF const static string null;

		rearray<char> data;

		string()
		{
		}

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

		string(const uti::string& other, uti::i64 offset)
		{
			assert(offset > 0 && offset < other.length());
			data.allocate_count(other.data.count - offset);
			memcpy(data.data, other.data.data + offset, other.data.count - offset);
		}

		string(i64 length)
		{
			data.allocate_count(length + 1, /*zero*/ true);
		}

		operator const char*()
		{
			return (const char*)data.data;
		}

		i64 length() const { return data.count-1; }
		char* raw() { return (char*)data.data; }
		const char* raw() const { return (const char*)data.data; }
		void zero() { memset(raw(), 0, length()*sizeof(char)); }
		bool is_null() { return data.capacity == 0; }
	};

	struct string_view;

	template <uti::i64 capacity>
	struct fixed_string
	{
		static_array<char, capacity+1> data;

		fixed_string()
		{
		}

		fixed_string(const char* str, uti::i64 len)
		{
			assert(len <= capacity);
			memcpy(data.data, str, len);
		}

		fixed_string(const char* str)
		{
			i64 str_len = strnlen(str, capacity);
			memcpy(data.data, str, str_len);
		}

		fixed_string(const uti::string& other)
		{
			data = other.data;
		}

		fixed_string(string_view start_view, string_view end_view)
		{
			i64 range_len = end_view.viewing - start_view.viewing;
			assert(range_len <= capacity && range_len < end_view.length());
			memcpy(data.data, start_view.viewing, range_len);
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
		TAT_DEF static const string_view null;

		const char* viewing;
		i64			len;

		string_view()
		{
			viewing = nullptr;
			len = 0;
		}

		// TODO: this seems kind of wonky we probably want this as a static function - create_string_view_raw?
		string_view(const char* view, i64 length) : viewing(view), len(length)
		{

		}

		string_view(const string& str) : string_view(str,0)
		{
		}

		string_view(const string& str, i64 offset) : viewing((const char*)str.data.data+offset), len(str.length() - offset)
		{
			assert(offset < str.length() && offset >= 0);
		}

		string_view(const string_view& str, i64 offset) : string_view(str)
		{
			// TODO: how the fuck do we check for validity?
			//assert(offset < str.length() && offset >= 0);
			viewing = viewing + offset;
			len -= offset;
		}

		operator const char*()
		{
			return viewing;
		}

		i64 length() const { return len; }
		const char* raw() const { return viewing; }
		bool is_null() { return viewing == nullptr && len == 0; }

		/* TODO: we need to trim the string
		operator string()
		{
		}*/
	};

	template <class string_type>
	string_type find_in_string(const string_type& in, const string& find, bool return_begin = true)
	{
		if (find.length() > in.length())
			return string_type::null;

		i64 pos = str::find_char(in.raw(), find.data[0], in.length());

		while (pos != UTI_STR_FIND_NOT_FOUND && pos < in.length() - find.length())
		{
			if (pos == UTI_STR_FIND_NOT_FOUND)
				return UTI_STR_FIND_NOT_FOUND;

			if (memcmp(in.raw() + pos, find.raw(), find.length()) == 0)
				return string_type(in, return_begin ? pos : pos + find.length());

			pos = str::find_char(in.raw(), find.data[0], find.length());
		}

		return string_type::null;
	}

	template <class string_type>
	string_type trim_whitespace_start(const string_type& in)
	{
		assert(in.length() > 0);
		i64 offset = 0;
		while (offset < in.length() && (in.raw()[offset] == '\n' || in.raw()[offset] == ' ' || in.raw()[offset] == '\t'))
		{
			offset++;
		}

		return string_type(in, offset);
	}
}

inline uti::string_view operator+(const uti::string& str, uti::i64 offset)
{
	return uti::string_view(str, offset);
}

inline uti::string_view operator-(const uti::string_view& str, uti::i64 offset)
{
	// TODO: there is zero protection for running of the begining of the string
	return uti::string_view(str.viewing - offset, str.len + offset);
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