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
		uti::i64 count;
		uti::i64 capacity;

		rearray();
		~rearray();

		void allocate(uti::i64 initial_capacity, bool zero = true);
		void rearray<T>::allocate_size(uti::i64 initial_size, bool zero = true);
		void reallocate(uti::i64 new_capacity, bool zero = true);
		void deallocate();

		T& operator[](uti::i64 idx);

		void add_end(T data, bool zero = true);
		T*	 add_end_ret(bool zero_if_grow = true);
		T*	 add_end(bool zero = true);
		void remove_end();
	};

	template <class T>
	rearray<T>::rearray()
	{
		data = nullptr;
		count = 0;
		capacity = 0;
	}

	template <class T>
	rearray<T>::~rearray()
	{
		deallocate();
	}

	template <class T>
	void rearray<T>::allocate(uti::i64 initial_capacity, bool zero = true)
	{
		assert(count == 0 && capacity == 0);
		data = new uti::u8[sizeof(T) * initial_capacity];
		capacity = initial_capacity;
		if (zero)
			memset(data, 0, sizeof(T) * capacity);
		count = 0;
	}

	template <class T>
	void rearray<T>::allocate_size(uti::i64 initial_size, bool zero = true)
	{
		data = new uti::u8[sizeof(T) * initial_size];
		capacity = initial_size;
		if (zero)
			memset(data, 0, sizeof(T) * capacity);
		count = initial_size;
	}

	template <class T>
	void rearray<T>::deallocate()
	{
		delete[] data;
		capacity = 0;
		count = 0;
	}

	template <class T>
	T& rearray<T>::operator[](uti::i64 idx)
	{
		assert(abs(idx) < count || (idx == -1 && count == 1));
		if (idx >= 0)
			return *(T*)(data + idx * sizeof(T));
		else
			return *(T*)(data + (count + idx) * sizeof(T));
	}

	template <class T>
	void rearray<T>::reallocate(uti::i64 new_capacity, bool zero = true)
	{
		uti::u8* old_data = data;
		data = new uti::u8[sizeof(T) * new_capacity];
		if (old_data != 0)
		{
			if (new_capacity > capacity)
			{
				memcpy(data, old_data, sizeof(T) * (new_capacity - capacity));
				if (zero)
					memset(data + sizeof(T) * capacity, 0, sizeof(T) * (new_capacity - capacity));
			}
			else
			{
				memcpy(data, old_data, sizeof(T) * new_capacity);
			}
			delete[] old_data;
		}
		else if (zero)
		{
			memset(data, 0, sizeof(T) * new_capacity);
		}
		capacity = new_capacity;
	}

	template <class T>
	void rearray<T>::add_end(T value , bool zero_if_grow = true)
	{
		T* new_value = add_end_ret(zero_if_grow);
		*new_value = value;
	}

	template <class T>
	T* rearray<T>::add_end(bool zero_if_grow = true)
	{
		if (count == capacity)
			reallocate(uti::max(capacity+1,capacity * 2), zero_if_grow);

		count++;

		return (T*)(data)+(count - 1);
	}

	template <class T>
	T* rearray<T>::add_end_ret(bool zero_if_grow = true)
	{
		add_end(zero_if_grow);
		return (T*)(data + (count-1) * sizeof(T));
	}

	template <class T>
	void rearray<T>::remove_end()
	{
		assert(count > 0);
		count--;
	}
}
