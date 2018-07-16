#pragma once
#include "construct.h"
#include "dafault_alloc.h"
#include "Type_Traits.h"
#include "Iterator_Traits.h"

template <class T, class Alloc = _Alloc>
class Vector
{
public:
	typedef T* Iterator;
	typedef ReverseIterator<Iterator> ReverseIterator;
	typedef T ValueType;
	typedef T* Poniter;
	typedef T& Reference;
	typedef int DifferenceType;
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef SimpleAlloc<T, Alloc> VectorAlloc;

	Vector()
		: _start(NULL)
		, _finish(NULL)
		, _endofstorage(NULL)
	{}

	ReverseIterator RBegin()
	{
		return ReverseIterator(End());
	}
	ReverseIterator REnd()
	{
		return ReverseIterator(Begin());
	}
	void PushBack(const T& data)
	{
		_CheckCapacity();
		Construct(_finish, data); //构造对象
		*_finish = data;
		_finish++;
	}

	void PopBack()
	{
		_finish--;
		Destory(_finish);
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	size_t Size()
	{
		return _finish - _start;
	}

	size_t Capacity()
	{
		return _endofstorage - _start;
	}

	bool Empty()
	{
		return _start == _finish;
	}

	T& operator[](size_t n)
	{
		return *(_start + n);
	}

	void Clear()
	{
		_finish = _start;
	}

	void Resize(size_t newsize, const T&data = T())
	{
		size_t oldsize = Size();
		if (newsize <= oldsize)
			_finish = _start + newsize;
		else
		{
			if (newsize < Capacity())
			{
				for (size_t index = oldsize; index < newsize; index++)
					*_finish++ = data;
			}
			else
			{//空间不够，newsize超过容量
				// 申请新空间
				T* tmp = VectorAlloc::Allocate(newsize);
				for (size_t i = 0; i < oldsize; i++)
					Construct(tmp + i, _start[i]);
				for (size_t i = oldsize; i < newsize; i++)
					Construct(tmp + i, data);
				// 释放旧空间
				Destroy(_start, _endofstorage);
				VectorAlloc::DeAllocate(_start, Capacity());
				_start = tmp;
				_finish = _start + newsize;
				_endofstorage = _start + newsize;
			}
		}
	}
private:
	void _CheckCapacity()
	{
		// if(size == capacity)
		size_t capacity = Capacity();
		size_t size = Size();
		if (_finish == _endofstorage)
		{
			size_t newcapacity = capacity * 2 + 3;
			T *tmp = VectorAlloc::Allocate(newcapacity);
			for (size_t i = 0; i < size; i++)
				Construct(tmp + i, _start[i]);
			for (size_t i = size; i < newcapacity; i++)
				Construct(tmp + i, T());
			Destory(_start, _endofstorage);
			VectorAlloc::DeAllocate(_start, capacity);

			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + newcapacity;
		}
	}
protected:
	void DeAllocate()
	{
		if (_start)
			VectorAlloc::DeAllocate(_start, _endofstorage - _start);
	}

private:
	Iterator _start;
	Iterator _finish;
	Iterator _endofstorage;
};


void test()
{
	//Vector<int> li;
	//li.PushBack(111);
	//li.PushBack(222);
	//li.PushBack(333);
	//Vector<int>::Iterator it = li.Begin();
	//while (it != li.End())
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	//Vector<int>::ReverseIterator rIt = li.RBegin();
	//while (rIt != li.REnd())
	//{
	//	cout << *rIt << " ";
	//	++rIt;
	//}
	//cout << endl;

	Vector<string> li;
	li.PushBack("111");
	li.PushBack("222");
	li.PushBack("333");
	Vector<string>::Iterator it = li.Begin();
	while (it != li.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	Vector<string>::ReverseIterator rIt = li.RBegin();
	while (rIt != li.REnd())
	{
		cout << *rIt << " ";
		++rIt;
	}
	cout << endl;
	li.PopBack();
}
