#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
///////////////////////////////////AutoPtr///////////////////////////////////////
template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		: _ptr(ptr)
	{}

	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return (*_ptr);
	}
	T* operator->()
	{
		return _ptr;
	}
	
	AutoPtr(AutoPtr& ap)
		: _ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	AutoPtr& operator=(AutoPtr& ap)
	{
		if (this != &ap)
		{
			if (_ptr)
				delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
private:
	T* _ptr;
};
int main()
{

	AutoPtr<int> ap1(new int);
	//AutoPtr<int> ap2(ap1);//缺陷：ap1将不能在使用
	AutoPtr<int> ap3;
	ap3 = ap1;
	//*ap1 = 10;
	*ap3 = 100;
	cout << *ap3 << endl;
	return 0;
}
////////////////////////////////////////AutoPtr///////////////////////////////////////
template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		: _ptr(ptr)
		, _owner(true)
	{
		if (NULL == _ptr)
			_owner = false;
	}
	AutoPtr(const AutoPtr& ap)
		: _ptr(ap._ptr)
		, _owner(ap._owner)
	{
		ap._owner = false;
	}
	AutoPtr& operator=(const AutoPtr& ap)
	{
		if (this != &ap)
		{
			if (_ptr)
				delete _ptr;
			_ptr = ap._ptr;
			_owner = ap._owner;
			ap._owner = false;
		}
		return *this;
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return (*_ptr);
	}
	~AutoPtr()
	{
		if (_ptr && _owner == true)
		{
			delete _ptr;
			_owner = false;
			_ptr = NULL;
		}
	}
private:
	T* _ptr;
	mutable bool _owner;
};
int main()
{
	AutoPtr<int> ap1(new int(1));
	if (true)//出了作用域ap2被释放，ap1仍然是false
		AutoPtr<int> ap2(ap1);
	cout << *ap1 << endl;
	
	return 0;
}
//////////////////////////////////////scoped_ptr///////////////////////////////////
template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr = NULL)
		: _ptr(ptr)
	{}
	~ScopedPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
private://防拷贝，将声明设为私有而不定义
	ScopedPtr(const ScopedPtr& sp);
	ScopedPtr& operator=(const ScopedPtr sp);
private:
	T* _ptr;
};
int main()
{
	ScopedPtr<int> sp1(new int(5));
	ScopedPtr<int> sp2(sp1);
	sp2 = sp1;
	*sp1 = 20;
	cout << *sp1 << endl;
	return 0;
}
////////////////////////////////////////shared_ptr///////////////////////////////////
template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = NULL)
		: _ptr(ptr)
		, _pCount(new int(0))
	{
		if (_ptr)
			*_pCount = 1;
	}
	SharedPtr(const SharedPtr& sp)
		: _ptr(sp._ptr)
		, _pCount(sp._pCount)
	{
		(*_pCount)++;
	}
	SharedPtr& operator=(const SharedPtr& sp)
	{
		if (this != &sp)
		{
			if (_pCount && --(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
			}
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (*_pCount)
				(*_pCount)++;
		}
		return *this;
	}
	~SharedPtr()
	{
		if (_ptr && --(*_pCount))
		{
			delete _ptr;
			_ptr = NULL;
          delete _pCount;
          _pConut=NULL;
		}
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
private:
	T* _ptr;
	int* _pCount;
};
#include <memory>
int main()
{
	SharedPtr<int> sp1(new int(5));
	//SharedPtr<int> sp2(sp1);
	SharedPtr<int> sp3;
	sp3 = sp1;
	*sp1 = 5;
	//sp3 = sp2;
	//*sp1 = 10;
	//cout << *sp1 << endl;
	//shared_ptr<int> sp5;
	return 0;

}
/////////////////////////////weak_ptr/////////////////////
#include <memory>//weak_ptr弱指针，必须与shared_ptr搭配使用，不能单独管理空间
template<class T>
struct Node
{
	Node(const T& data)
	: _data(data)
	//, _pPre(NULL)
	//, _pNext(NULL)
	{
		cout << "Node()" << this << endl;
	}
	T _data;
	weak_ptr<Node<T>> _pNext;
	weak_ptr<Node<T>> _pPre;
	~Node()
	{
		cout << "~Node()" << this << endl;
	}
};

int main()
{
	shared_ptr<Node<int>> sp1(new Node<int>(10));
	shared_ptr<Node<int>> sp2(new Node<int>(20));
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
	sp1->_pNext = sp2;
	sp2->_pPre = sp1;
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
	return 0;
}