/*
	Reallocating array once it hits capacity
*/

#pragma once

#include <assert.h>

namespace uti
{
	template <class T>
	struct rearray
	{
		uti::u8* data;
		uti::i64 size;
		uti::i64 capacity;

		void allocate(uti::i64 initial_capacity, bool zero = true);
		void rearray<T>::allocate_size(uti::i64 initial_size, bool zero = true);
		void reallocate(uti::i64 new_capacity, bool zero = true);
		void deallocate();

		T& operator[](uti::i64 idx);

		void add_end(T data, bool zero = true);
		void add_end(bool zero = true);
		void remove_end();
	};

	template <class T>
	void rearray<T>::allocate(uti::i64 initial_capacity, bool zero = true)
	{
		data = new uti::u8[sizeof(T) * initial_capacity];
		capacity = initial_capacity;
		if (zero)
			memset(data, 0, sizeof(T) * capacity);
		size = 0;
	}

	template <class T>
	void rearray<T>::allocate_size(uti::i64 initial_size, bool zero = true)
	{
		data = new uti::u8[sizeof(T) * initial_size];
		capacity = initial_size;
		if (zero)
			memset(data, 0, sizeof(T) * capacity);
		size = initial_size;
	}

	template <class T>
	void rearray<T>::deallocate()
	{
		delete[] data;
		capacity = 0;
		size = 0;
	}

	template <class T>
	T& rearray<T>::operator[](uti::i64 idx)
	{
		assert(idx < size);
		if (idx >= 0)
			return *(T*)(data + idx * sizeof(T));
		else
			return *(T*)(data + (size + idx) * sizeof(T));
	}

	template <class T>
	void rearray<T>::reallocate(uti::i64 new_capacity, bool zero = true)
	{
		uti::u8* old_data = data;
		data = new uti::u8[sizeof(T) * new_capacity];
		if (new_capacity > capacity)
		{
			memcpy(data, old_data, sizeof(T) * (new_capacity - capacity));
			if(zero)
				memset(data + sizeof(T) * capacity, 0, sizeof(T) * (new_capacity - capacity));
		}
		else
		{
			memcpy(data, old_data, sizeof(T) * new_capacity);
		}
		delete[] old_data;
		capacity = new_capacity;
	}

	template <class T>
	void rearray<T>::add_end(T value , bool zero = true)
	{
		if(size == capacity)
			reallocate(capacity * 2, zero);

		*(T*)(data + size++ * sizeof(T)) = value;
	}

	template <class T>
	void rearray<T>::add_end( bool zero = false )
	{
		if (size == capacity)
			reallocate(capacity * 2, zero);

		size++;
	}

	template <class T>
	void rearray<T>::remove_end()
	{
		assert(size > 0);
		size--;
	}
}