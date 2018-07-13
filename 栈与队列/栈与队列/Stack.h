#include "Vector.h"
#include "List.h"
#if 1
template<class T, class Container = Vector<T>>
class Stack
{
public:
	Stack()
	{}
	Stack(T* arr, size_t size)
	{
		for (size_t i = 0; i < size; i++)
			Push(arr[i]);
	}
	void Push(const T& data)
	{
		_c.PushBack(data);
	}
	void Pop()
	{
		_c.PopBack();
	}
	bool Empty()const
	{
		return _c.Empty();
	}
	size_t Size()
	{
		return _c.Size();
	}
	T& Top()
	{
		return _c.Back();
	}
	const T& Top()const
	{
		return _c.Back();
	}
private:
	Container _c;
};
#endif 


#if 0
template<class T, template<class > class Container = Vector>
class Stack
{
public:
	Stack()
	{}
	void Push(const T& data)
	{
		_c.PushBack(data);
	}
	void Pop()
	{
		_c.PopBack();
	}
	bool Empty()
	{
		return _c.Empty();
	}
	size_t Size()
	{
		return _c.Size();
	}
	T& Top()
	{
		return _c.Back();
	}
	const T& Top()const
	{
		return _c.Back();
	}
private:
	Container<T> _c;
};
#endif
