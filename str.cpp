#include "stdafx.h"

#include "tat.h"

#include "str.h"

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

uti::i64 str::find_char(uti::cstr src, char ch, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] == ch)
			return i;
	}

	return UTI_STR_FIND_NOT_FOUND;
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

uti::i64 str::find_num_char(uti::cstr src, char ch, uti::i64 str_len)
{
	for (uti::i64 i = 0; i < str_len; i++)
	{
		if (src[i] != ch)
			return i;
	}

	return i64_max;
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
