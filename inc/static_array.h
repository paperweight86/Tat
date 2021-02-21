/*
	Static capacity array.
	
	- Negative indexing is supported based on count.
*/
#pragma once

#include <assert.h>

#include <types.h>

namespace uti
{
	template <class T, uti::i64 capacity>
	struct static_array
	{
		uti::u8 data[capacity*sizeof(T)];
		uti::i64 count;

		static_array(bool zero = false);
		~static_array();

		T& operator[](uti::i64 idx);
		T* ptr_at(uti::i64 idx);

		uti::i64 push_back(T& thing);
		T*		 push_back(bool zero = false);
		void pop_back(bool zero = false);
	};

	template <class T, uti::i64 capacity>
	static_array<T, capacity>::static_array(bool zero)
	{
		if (zero)
		{
			memset(&data[0], 0, sizeof(T)*capacity);
		}
		count = 0;
	}

	template <class T, uti::i64 capacity>
	static_array<T, capacity>::~static_array()
	{
	}

	template <class T, uti::i64 capacity>
	T& static_array<T, capacity>::operator[](uti::i64 idx)
	{
		assert(llabs(idx) < count || (idx == -1 && count == 1));
		if (idx >= 0)
			return *(T*)(data + idx * sizeof(T));
		else
			return *(T*)(data + (count + idx) * sizeof(T));
	}

	template <class T, uti::i64 capacity>
	T* static_array<T, capacity>::ptr_at(uti::i64 idx)
	{
		assert(llabs(idx) < count || (idx == -1 && count == 1));
		if (idx >= 0)
			return (T*)(data + idx * sizeof(T));
		else
			return (T*)(data + (count + idx) * sizeof(T));
	}

	template <class T, uti::i64 capacity>
	uti::i64 static_array<T, capacity>::push_back(T& thing)
	{
		assert(count + 1 < capacity);
		this[count] = thing;
		return count++;
	}

	template <class T, uti::i64 capacity>
	T* static_array<T, capacity>::push_back(bool zero)
	{
		assert(count + 1 < capacity);
		if (zero)
		{
			memset(ptr_at(count), 0, sizeof(T));
		}
		return ptr_at(count++);
	}

	template <class T, uti::i64 capacity>
	void static_array<T, capacity>::pop_back(bool zero)
	{
		assert(count != 0);
		count--;
		if (zero)
		{
			memset(ptr_at(count), 0, sizeof(T));
		}
	}
}
#pragma once
