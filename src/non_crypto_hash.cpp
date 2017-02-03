#include "stdafx.h"

#include "non_crypto_hash.h"

#include "src\ext\murmur_hash_3.h"

uti::u32 uti::non_crypto_hash_32(void* data, u32 len, u32 seed)
{
	uti::u32 result = 0;
	MurmurHash3_x86_32(data, len, seed, &result);
	return result;
}
