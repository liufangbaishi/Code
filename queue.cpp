#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;
//循环队列
#if 0
template <class T, size_t N = 4>
class Queue
{
public:
	Queue()
		: _front(0)
		, _back(0)
		, _count(0)
	{}
	void Push(const T& data)
	{
		if (_count == N)
			return;
		_arr[_back++] = data;
		_count++;
		if (_back == N)
			_back = 0;//循环
	}
	void Pop()
	{
		if (0 == _count)
			assert(0);
		_front++;
		_count--;
		if (N == _front)//最后一个
			_front = 0;
	}
	size_t Size()const
	{
		return _count;
	}
	T& Front()
	{
		return _arr[_front];
	}
	const T& Front()const
	{
		return _arr[_front];
	}
	T& Back()
	{
		return _arr[(_back - 1 + N) % N];
		//retrun _arr[(_front+_count-1)%N];
	}
	const T& Back()const
	{
		retrun _arr[(_front+_count-1)%N];
	}
private:
	T _arr[N];
	int _front;
	int _back;
	int _count;
};
int main()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Pop();
	q.Push(4);
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	return 0;
}

#endif
#if 0
template <class T, size_t N = 4>
class Queue
	//使用循环，少存储一个数字
{
public:
	Queue()
		: _front(0)
		, _rear(0)
	{}
	void Push(const T& data)
	{
		if ((_rear+1)%N == _front)
			return;
		_arr[_rear++] = data;
		if (_rear == N)
			_rear = 0;//循环
	}
	void Pop()
	{
		if (_front == _rear)
			assert(0);
		_front++;
		if (N == _front)//最后一个
			_front = 0;
	}
	size_t Size()const
	{
		int cur = _front;
		int count = 1;
		if (_front == _rear)//没有元素返回0
			return 0;
		while (((cur+1)%N) != _rear)
		{
			count++;
			cur++;
		}
		return count;
	}
	T& Front()
	{
		return _arr[_front];
	}
	const T& Front()const
	{
		return _arr[_front];
	}
	T& Back()
	{		
		return _arr[(_rear - 1 + N) % N];
	}
	const T& Back()const
	{		
		return _arr[(_rear - 1 + N) % N];
	}
private:
	T _arr[N];
	int _front;
	int _rear;
};
#endif

#if 1
template <class T, size_t N = 4>
class Queue
	//使用标志，push元素置true,pop置false
{
public:
	Queue()
		: _front(0)
		, _rear(0)
		, flag(0)
	{}
	void Push(const T& data)
	{
		if (_front == _rear && flag == 1)//满了
			return;
		_arr[_rear++] = data;
		flag = 1;
		if (_rear == N)
			_rear = 0;//循环
	}
	void Pop()
	{
		if (_front == _rear && flag == 0)//空
			assert(0);
		_front++;
		flag = 0;
		if (N == _front)//最后一个
			_front = 0;
	}
	size_t Size()const
	{
		int cur = _front;
		int count = 1;
		if (_front == _rear && flag == 0)//没有元素返回0
			return 0;
		while (((cur + 1) % N) != _rear)
		{
			count++;
			cur++;
		}
		return count;
	}
	T& Front()
	{
		return _arr[_front];
	}
	const T& Front()const
	{
		return _arr[_front];
	}
	T& Back()
	{
		return _arr[(_rear - 1 + N) % N];
	}
	const T& Back()const
	{
		return _arr[(_rear - 1 + N) % N];
	}
private:
	T _arr[N];
	int _front;
	int _rear;
	bool flag;
};
int main()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Pop();
	q.Push(4);
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Pop();
	q.Pop();
	q.Pop();
	//q.Pop();
	cout << q.Size() << endl;
	return 0;
}
#endif

#if 0
template <class T>
struct Node
{
	T _data;
	Node* _pNext;
	Node(const T& data)
		: _data(data)
		, _pNext(NULL)
	{}
};
template <class T>
class Queue
{
	typedef Node<T> Node;
public:
	Queue()
		: _front(NULL)
		, _back(NULL)
	{}
	void Push(const T& data)
	{
		Node* pNewNode = new Node(data);
		if (NULL == _back)
			_front = _back = pNewNode;
		else
		{
			_back->_pNext = pNewNode;
			_back = _back->_pNext;
		}
	}
	void Pop()
	{
		if (_front == NULL)
			return;
		_front = _front->_pNext;
	}
	size_t Size()const
	{
		size_t count = 0;
		Node* pcur = _front;
		while (pcur)
		{
			pcur = pcur->_pNext;
			count++;
		}
		return count;
	}
	T& Front()
	{
		assert(_front);
		return _front->_data;
	}
	const T& Front()const
	{
		assert(_front);
		return _front->_data;
	}
	T& Back()
	{
		assert(_back);
		return _back->_data;
	}
	const T& Back()const
	{
		assert(_back);
		return _back->_data;
	}
	~Queue()
	{
		while (_front)
		{ 
			Node* pdel = _front;
			_front = _front->_pNext;
			delete pdel;
			pdel = NULL;
		}
	}
private:
	Node* _front;
	Node* _back;
};
int main()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Pop();
	q.Pop();
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;

	q.Push(4);
	//q.Pop();
	//q.Pop();
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Size() << endl;
	return 0;
}

#endif