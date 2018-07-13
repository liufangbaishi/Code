#include "Vector.h"
#include "List.h"
#if 1
template <class T, class Container = List<T>>
class Queue
{
public:
	Queue()
	{}
	void Push(const T& data)
	{
		_q.PushBack(data);
	}
	void Pop()
	{
		_q.PopFront();
	}
	bool Empty()const
	{
		return _q.Empty();
	}
	size_t Size()
	{
		return _q.Size();
	}
	T& Front()
	{
		return _q.Front();
	}
	const T& Front()const
	{
		return _q.Front();
	}
	T& Back()
	{
		return _q.Back();
	}
	const T& Back()const
	{
		return _q.Back();
	}
private:
	Container _q;
};
#endif 
#if 0
template <class T,template<class > class Container = List>
class Queue
{
public:
	Queue()
	{}
	void Push(const T& data)
	{
		_q.PushBack(data);
	}
	void Pop()
	{
		_q.PopFront();
	}
	bool Empty()const
	{
		return _q.Empty();
	}
	size_t Size()
	{
		return _q.Size();
	}
	T& Front()
	{
		return _q.Front();
	}
	const T& Front()const
	{
		return _q.Front();
	}
	T& Back()
	{
		return _q.Back();
	}
	const T& Back()const
	{
		return _q.Back();
	}
private:
	Container<T> _q;
};
#endif