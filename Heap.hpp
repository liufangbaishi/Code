#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct Less//小堆
{
	bool operator()(const T& left, const T& right)
	{
		return left->_data < right->_data;
	}
}; 

template <class T>
struct Greater//大堆
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template <class T, class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(T *arr, size_t size)
	{
		_arr.resize(size);
		for (size_t i = 0; i < size; i++)
			_arr[i] = arr[i];
		if (size > 1)
		{
			int root = (size - 2) / 2;//size_t的数据大于等于0造成死循环
			for (; root >= 0; root--)
				_AdjustDown(root);
		}
	}

	void Push(const T& data)
	{
		_arr.push_back(data);
		size_t size = _arr.size();
		if (size > 1)
			_AdjustUp(size - 1);
	}

	void Pop()
	{
		size_t size = _arr.size();
		if (_arr.empty())
			return;
		swap(_arr[0], _arr[size - 1]);
		_arr.pop_back();
		if (_arr.size() > 1)
			_AdjustDown(0);
	}

	bool Empty()const
	{
		return _arr.empty();
	}

	size_t Size()const
	{
		return _arr.size();
	}

	T Top()const
	{
		return _arr[0];
	}

private:
	void _AdjustDown(size_t parent)
	{
		size_t child = parent * 2 + 1;
		size_t size = _arr.size();
		while (child < size)
		{
			if (child + 1 < size && Compare()(_arr[child + 1], _arr[child]))
				child += 1;
			if (Compare()(_arr[child], _arr[parent]))
			{
				swap(_arr[parent], _arr[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}

	void _AdjustUp(size_t child)
	{
		size_t parent = (child - 1) / 2;
		size_t size = _arr.size();
		while (child > 0)
		{
			if (Compare()(_arr[child], _arr[parent]))
			{
				swap(_arr[parent], _arr[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	vector<T> _arr;
};

//void test()
//{
//	int arr[] = { 1, 2, 3, 4, 5 };
//	Heap<int, Greater<int>> h(arr, sizeof(arr) / sizeof(arr[0]));
//	h.Push(6);
//	h.Pop();
//	cout << h.Empty() << endl;
//	cout << h.Size() << endl; 
//	cout << h.Top() << endl;
//}