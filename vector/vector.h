#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>

template<class T>
class vectors
{
public:
	typedef T* iterator;
	typedef const T* constIterator;
	vectors() :_start(nullptr), _finish(nullptr), _ends(nullptr) {}
	vectors(const size_t pos, const T& val = T())
	{
		_start = new T[pos];
		for (size_t i = 0; i < pos; i++)
		{
			_start[i] = val;
		}
		_finish = _start + pos;
		_ends = _start + pos;
	}
	size_t size()
	{
		return _finish - _start;
	}
	iterator begin()
	{
		return _start;
	}
	iterator end()
	{
		return _finish;
	}
	T& operator[](size_t pos)
	{
		assert(pos < size());
		return _start[pos];
	}
	T& at(size_t pos)
	{
		assert(pos < size());
		return _start[pos];
	}
	void push_back(const T& val)
	{
		if (_finish == _ends)
		{
			size_t memory = _start == nullptr ? 1 : 2 * capacity();
			reserve(memory);
		}
		*_finish = val;
		++_finish;
	}
	size_t capacity()
	{
		return _ends - _start;
	}
	void reserve(size_t n)
	{
		size_t len = size();
		if (n > size())
		{
			T* temp = new T[n];
			for (int i = 0;i < len;i++)
			{
				temp[i] = _start[i];
			}
			delete[] _start;
			_start = temp;
			_finish = _start + len;
			_ends = _start + n;
		}
	}
	void assign(size_t n, const T& val)
	{
		resize(n);
		for (int i = 0; i < n; i++)
		{
			_start[i] = val;
		}
	}
	void assign(iterator first, iterator last)//需要注意这里传进来的是迭代器(抽象的对象),所以不是和指针一样表示偏移，但类似
	{
		size_t n = last - first;
		resize(n);
		iterator pos = _start;
		for (iterator message = first;message != last;message++)
		{
			*pos = *message;
			++pos;
		}
	}
	void assign(std::initializer_list<T>val)//列表初始化的一种方式
	{
		size_t len = val.size();
		resize(len);
		iterator pos = _start;
		for (auto message : val)
		{
			*pos = message;
			++pos;
		}
	}
	void resize(size_t n,T val = T())
	{
		if (n >= capacity())
		{
			reserve(n);
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
			_ends = _start + n;
		}
		_finish = _start + n;
	}
	iterator insert(iterator pos, const T& val)
	{
		size_t len = pos - _start;
		if (_finish == _ends)//必须加判断，这个函数会扩容,同时避免capacity大小为0的情况
		{
			size_t count = _start == nullptr ? 1 : 2 * capacity();
			reserve(count);
		}
		iterator position = _finish;
		pos = _start + len;
		while (position != pos)
		{
			*position = *(position - 1);
			position--;
		}
		*pos = val;
		++_finish;
		return pos;
	}
	void insert(iterator pos, size_t n, const T& val)
	{
		size_t len = pos - _start;
		if (_finish == _ends)
		{
			size_t count = _start == nullptr ? 1 : 2 * capacity();
			reserve(count);
		}
		size_t counter = capacity();
		while ((size() + n) > counter)
		{
			counter *= 2;
		}
		reserve(counter);
		iterator position = _finish + n;
		pos = _start + len;
		if (_finish == _start)
		{
			while (pos < position)
			{
				*pos = val;
				++pos;
			}
			_finish = _start + size() + n;
			return;
		}
		while(position != pos)
		{
			if (position > pos + n)
			{
				--position;
				*position = *(position - n);
			}
			else
			{
				--position;
				*position = val;
			}
		}
		_finish = _start + size() + n;
	}
	template<class inputIterator>
	void insert(inputIterator pos, inputIterator first, inputIterator last)
	{
		size_t len = pos - _start;
		size_t n = last - first;
		if (_finish == _ends)
		{
			size_t memory = _start == nullptr ? 1 : 2 * capacity();
			reserve(memory);
		}
		size_t counter = capacity();
		if (size() + n > counter)
		{
			counter *= 2;
		}
		reserve(counter);
		iterator position = _finish + n;
		pos = _start + len;
		if (_finish == _ends)
		{
			while (first != last)
			{
				*pos = *first;
				pos++;
				first++;
			}
			_finish = _start + n;
			return;
		}
		while (position != pos && last != first)
		{
			if (position > pos + n)
			{
				--position;
				*position = *(position - n);
			}
			else
			{
				--position;
				--last;
				*position = *last;
			}
		}
		_finish = _start + size() + n;
	}
	void swap(vectors<T>& vecs)//swap的内部原理不清楚，没有写出交换方法，下面是系统自带swap,添加头文件algorithm
	{
		std::swap(_start, vecs._start);
		std::swap(_finish, vecs._finish);
		std::swap(_ends, vecs._ends);
	}
	T front()
	{
		return *_start;
	}
	T back()
	{
		return *(_finish - 1);
	}
	iterator erase(iterator pos)
	{
		assert(pos >= begin() && pos <= end());
		while (pos != (_finish - 1))
		{
			*pos = *(pos + 1);
			++pos;
		}
		--_finish;
		return pos;
	}
	iterator erase(iterator first, iterator last)
	{
		assert(first >= begin() && last <= end());
		while (last != first)
		{
			--last;
			--_finish;
			*last = *_finish;
		}
		return first;
	}
	void pop_back()
	{
		--_finish;
	}
	void clear()
	{

	}
	~vectors()
	{
		delete[] _start;
		_ends = _finish = _start = nullptr;
	}
	void shrink_to_fit()
	{
		_ends = _finish;
	}
	//完成大部分常用功能，反向迭代器未写结束。
private:
	iterator _start;
	iterator _finish;
	iterator _ends;
};
