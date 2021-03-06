#include "stdafx.h"

#include "tat.h"

#include "str.h"

#include <ctype.h>

const uti::string_view uti::string_view::null = uti::string_view();
const uti::string uti::string::null = uti::string();

uti::i64 str::strOffToNextFloat(uti::tstr c, uti::i64 l)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(c + off);

	while (!STR_CHAR_IS_NUM(c + off)
		&& !STR_CHAR_IS_NEGNUM_START(c + off, off + 1, l, c + off + 1)
		&& off < l
		&& c+off != 0)
	{
		lastWasNum = STR_CHAR_IS_NUM(c + off);
		++off;
	}

	return off;
}

char* str::strOffToNextFloatPtr(char* c, uti::i64 l)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(c + off);

	while (!STR_CHAR_IS_NUM(c + off)
		&& !STR_CHAR_IS_NEGNUM_START(c + off, off + 1, l, c + off + 1)
		&& off < l
		&& c + off != 0)
	{
		lastWasNum = STR_CHAR_IS_NUM(c + off);
		++off;
	}
	if (!STR_CHAR_IS_NUM(c + off) && !STR_CHAR_IS_NEGNUM_START(c + off, off + 1, l, c + off + 1))
		return nullptr;
	return c + off;
}

uti::i64 str::strOffToEndFloat(uti::tstr c, uti::i64 l)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(c + off);

	while ((STR_CHAR_IS_NUM(c + off)
		|| STR_CHAR_IS_DECIMAL_POINT(c + off)
		|| (STR_CHAR_IS_NEGNUM_START(c + off, off + 1, l, c + off + 1) && off == 0)
		|| (lastWasNum && STR_CHAR_IS_SCIFLT_EXPONENT(c + off)))
		&& off < l
		&& c + off != 0)
	{
		lastWasNum = STR_CHAR_IS_NUM(c + off);
		++off;
	}

	return off;
}

char* str::strOffToEndFloatPtr(char* c, uti::i64 l)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(c + off);

	while ((STR_CHAR_IS_NUM(c + off)
		|| STR_CHAR_IS_DECIMAL_POINT(c + off)
		|| (STR_CHAR_IS_NEGNUM_START(c + off, off + 1, l, c + off + 1) && off == 0)
		|| (lastWasNum && STR_CHAR_IS_SCIFLT_EXPONENT(c + off)))
		&& off < l
		&& c + off != 0)
	{
		lastWasNum = STR_CHAR_IS_NUM(c + off);
		++off;
	}

	return c + off;
}

char* str::find_integer_ptr(char* str, uti::i64 str_len)
{
	char* cur = str;
	while (!STR_CHAR_IS_NUM(cur) && cur - str < str_len) { cur++; }
	if (STR_CHAR_IS_NUM(cur))
	{
		if (cur != str && *(cur - 1) == '-')
		{
			return cur - 1;
		}
		else
		{
			return cur;
		}
	}
	else
	{
		return nullptr;
	}
}

uti::i64 str::find_char(uti::cstr src, char ch, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] == ch)
			return i;
	}

	return UTI_STR_FIND_NOT_FOUND;
}

char* str::find_char_ptr(char* src, char ch, uti::i64 str_len)
{
	char* cur = src;
	while (*cur != ch && cur - src < str_len) { cur++; }

	return *cur == ch? cur : nullptr;
}

uti::i64 str::find_not_char(uti::cstr src, char ch, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] != ch)
			return i;
	}

	return UTI_STR_FIND_NOT_FOUND;
}

uti::i64 str::find_last_char(uti::cstr src, char ch, uti::i64 str_len)
{
	uti::i64 idx = UTI_STR_FIND_NOT_FOUND;
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] == ch)
			idx = i;
	}

	return idx;
}

uti::i64 str::find_num_char(uti::cstr src, char ch, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] != ch)
			return i;
	}

	return i64_max;
}

uti::i64 str::find_any_char(uti::cstr src, uti::cstr chars, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		char* cur = (char*)chars;
		while(*cur != '\0')
		{
			if (src[i] == *cur)
				return i;
			++cur;
		}
	}

	return UTI_STR_FIND_NOT_FOUND;
}

//!< Finds a word within a string by assuming it's surrounded by whitespace
uti::i64 str::find_word(uti::cstr find, uti::i64 find_len, char* src, uti::i64 str_len)
{
	if (str_len < find_len)
		return i64_max;

	const uti::i64 buffer_size = 256;
	//		char buff[buffer_size] = {};
	//		uti::i64 buffer_usage = find_len + 2;
	char* cur_str = src;
	//		uti::i64 cur_offset = 0;
	for (uti::i64 i = 0; i < str_len; i++)
	{
		// TODO: [DanJ] Slide a window through the file looking for the string surrounded by whitespace
		if (strncmp(cur_str + i, find, find_len) == 0)
		{
			return i;
		}
	}

	return i64_max;
}

uti::i64 str::find_number(uti::tstr str, uti::i64 str_len)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(str + off);

	while (!STR_CHAR_IS_NUM(str + off)
		&& !STR_CHAR_IS_NEGNUM_START(str + off, off + 1, str_len, str + off + 1)
		&& off < str_len)
	{
		lastWasNum = STR_CHAR_IS_NUM(str + off);
		++off;
	}

	return off;
}

uti::i64 str::find_end_number(uti::tstr str, uti::i64 str_len)
{
	uti::i64 off = 0;
	bool lastWasNum = STR_CHAR_IS_NUM(str + off);

	while ((STR_CHAR_IS_NUM(str + off)
		|| STR_CHAR_IS_DECIMAL_POINT(str + off)
		|| (STR_CHAR_IS_NEGNUM_START(str + off, off + 1, str_len, str + off + 1) && off == 0)
		|| (lastWasNum && STR_CHAR_IS_SCIFLT_EXPONENT(str + off)))
		&& off < str_len)
	{
		lastWasNum = STR_CHAR_IS_NUM(str + off);
		++off;
	}

	return off;
}

void	str::to_lower_inplace(uti::mstr str, uti::i64 str_len)
{
	uti::mstr c = str;
	uti::i64 i = 0;
	while(*c != '\0' && i < str_len)
	{
		*c = (char)tolower(*c);
		c++; i++;
	}
}

bool str::string_to_float(char* str, uti::i64 len, float* out_float, char** out_str_after)
{
	float result = 0.0f;
	char* cur = str;
	if (len == 0)
		return false;
	int i = 0;
	bool negate = false;
	if (STR_CHAR_IS_NEGNUM_START(cur, 1, len, cur+1))
	{
		negate = true;
		++cur;
		++i;
	}
	bool integer_part = true;
	float div = 1.0f;
	while (cur - str < len && cur != '\0')
	{
		if (STR_CHAR_IS_NUM(cur))
		{
			i++;
			if (integer_part)
			{
				result *= 10.0f;
				result += (float)(*cur - '0');
			}
			else
			{
				div *= 10.0f;
				result += (float)(*cur - '0') / div;
			}
		}
		else if (STR_CHAR_IS_DECIMAL_POINT(cur))
		{
			integer_part = false;
		}
		// TODO: sci exp representation
		//else if(STR_CHAR_IS_SCIFLT_EXPONENT)
		//{}
		else if (i == 0)
		{
			// No numbers were read
			return false;
		}
		else
		{
			break;
		}

		++cur;
	}

	if (negate)
	{
		result *= -1.0f;
	}

	if (out_str_after)
	{
		*out_str_after = cur;
	}

	assert(out_float != nullptr);
	*out_float = result;
	return true;
}

bool str::string_to_u32(char* str, uti::i64 len, uti::u32* out_u64, char** out_str_after)
{
	uti::u32 result = 0;
	char* cur = str;
	if (len == 0)
		return false;
	int i = 0;
	while (cur - str < len && cur != '\0')
	{
		if (STR_CHAR_IS_NUM(cur))
		{
			i++;
			result *= 10;
			result += (uti::u32)(*cur - '0');
			// TODO: Check for overflow
		}
		else if (i == 0)
		{
			// No numbers were read
			return false;
		}
		else
		{
			break;
		}

		++cur;
	}

	if (out_str_after)
	{
		*out_str_after = cur;
	}

	assert(out_u64 != nullptr);
	*out_u64 = result;

	return true;
}

bool str::read_floats(char* str, uti::i64 len, float* out_float, uti::i64 num_out_float, char** out_ptr)
{
	char* next_float = str;
	for (int i = 0; i < num_out_float; ++i)
	{
		next_float = str::strOffToNextFloatPtr(next_float, len - (next_float - str));
		if (next_float == nullptr || next_float - str > len)
			return false;
		if (!string_to_float(next_float, len - (next_float - str), out_float + i, &next_float))
			return false;
		//out_float[i] = strtof(next_float, &next_float);
	}

	if (out_ptr)
	{
		*out_ptr = next_float;
	}

	return true;
}

uti::i64 str::read_any_floats(char* str, uti::i64 len, float* out_float, uti::i64 max_floats, char** out_ptr)
{
	char* next_float = str;
	int i;
	for (i = 0; i < max_floats; ++i)
	{
		next_float = str::strOffToNextFloatPtr(next_float, len - (next_float - str));
		if (next_float == nullptr || next_float - str > len)
			return i;
		if (!string_to_float(next_float, len - (next_float - str), out_float + i, &next_float))
			break;
		//out_float[i] = strtof(next_float, &next_float);
	}

	if (out_ptr)
	{
		*out_ptr = next_float;
	}

	return i;
}

uti::i64 str::read_any_u32(char* str, uti::i64 len, uti::u32* out_integer, uti::i64 max_integers, char** out_ptr)
{
	char* next_integer = str;
	uti::i64 i;
	for (i = 0; i < max_integers; ++i)
	{
		next_integer = str::find_integer_ptr(next_integer, len - (next_integer - str));
		if (next_integer == nullptr || next_integer - str > len)
			return i;
		if (!string_to_u32(next_integer, len - (next_integer - str), out_integer + i, &next_integer))
			break;
		//out_float[i] = strtof(next_float, &next_float);
	}

	if (out_ptr)
	{
		*out_ptr = next_integer;
	}

	return i;
}
