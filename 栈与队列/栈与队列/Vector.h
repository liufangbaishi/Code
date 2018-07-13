#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
template <typename T>
class Vector
{
public:
	typedef T* Iterator;
	Vector()
		: _start(0)
		, _finish(0)
		, _endofstorage(0)
	{}
	Vector(const T* arr, size_t size)
		: _start(new T[size])
		, _finish(_start)//_finish(_start + size)
		, _endofstorage(_start + size)
	{
		for (size_t i = 0; i < size; i++)
			*_finish++ = arr[i];//_start[i] = arr[i];
	}
	Vector(const Vector<T>& v)
	{
		size_t size = v.Size();
		_start = new T[size];
		for (size_t i = 0; i < size; i++)
			_start[i] = v._start[i];
		_finish = _start + size;
		_endofstorage = _finish;
	}
	Vector& operator=(const Vector<T>& v)
	{
		size_t size = v.Size();
		if (this != &v)
		{
			T* tmp = new T[size];
			for (size_t i = 0; i < size; i++)
				tmp[i] = v._start[i];
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _finish;
		}
		return *this;
	}
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = NULL;
		}
	}
	//////////////////////Iterator////////////////////////////
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	//////////////////////Modify//////////////////////////////
	void PushBack(const T& data)
	{
		_CheckCapacity();
		*_finish = data;
		_finish++;
	}
	void PopBack()
	{
		assert(_start < _finish);
		_finish--;
	}
	void PopFront()
	{
		assert(_start < _finish);
		Iterator it = Begin();
		for (; it != End(); it++)
			*it = *(it+1);
		_finish--;
	}
	void Insert(size_t pos, const T& data)//任意位置插入
	{
		assert(pos <= Size());
		_CheckCapacity();
		for (size_t i = Size(); i > pos; i--)
			_start[i] = _start[i - 1];
		_start[pos] = data;
		_finish++;
	}
	void Erase(size_t pos)//任意位置删除
	{
		assert(pos <= Size());
		for (size_t i = pos; i < Size(); i++)
			_start[i] = _start[i + 1];
		_finish--;
	}
	/////////////////////Capacity///////////////////////////
	size_t Size()const
	{
		return _finish - _start;
	}
	size_t Capacity()const
	{
		return _endofstorage - _start;
	}
	bool Empty()const
	{
		if (_finish == _start)
			return true;
		return false;
	}
	void Resize(size_t newSize, const T& data = T())
	{
		size_t oldsize = Size();
		size_t capacity = Capacity();
		if (newSize <= oldsize)
			_finish = _start + newSize;
		else if (newSize > oldsize && newSize <= capacity)
		{
			for (size_t i = oldsize; i < newSize; i++)
				*_finish++ = data;

		}
		else
		{
			T* tmp = new T[newSize];
			for (size_t i = 0; i < oldsize; i++)
				tmp[i] = _start[i];
			for (size_t i = oldsize; i < newSize; i++)
				tmp[i] = data;
			delete[] _start;
			_start = tmp;
			_finish = _start + newSize;
			_endofstorage = _start + newSize;
		}
	}
	////////////////////Element Access//////////////////////
	T& operator[](size_t index)
	{
		assert(index <= Capacity());
		return _start[index];
	}
	const T& operator[](size_t index)const
	{
		assert(index <= Capacity());
		return _start[index];
	}
	T& Front()
	{
		assert(_start != _finish);
		return *_start;
	}
	const T& Front()const
	{		assert(_start != _finish);
		return *_start;
	}
	T& Back()
	{
		assert(_start != _finish);
		return *(_finish - 1);
	}
	const T& Back()const
	{
		assert(_start != _finish);
		return *(_finish - 1);
	}
	void Clear()
	{
		_finish = _start;
	}
	template<class T>
	friend ostream& operator<<(ostream& _cout, const Vector<T>& v)
	{
		for (size_t i = 0; i < v.Size(); i++)
			_cout << v._start[i] << " ";
		return _cout;
	}
private:
	void _CheckCapacity()
	{
		size_t size = Size();
		size_t capacity = Capacity();
		size_t newCapacity = 2 * capacity + 3;
		if (size >= capacity)
		{
			T* tmp = new T[newCapacity];
			for (size_t i = 0; i < size; i++)
				tmp[i] = _start[i];
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + newCapacity;
		}
	}
private:
	T* _start;
	T* _finish;
	T* _endofstorage;
};