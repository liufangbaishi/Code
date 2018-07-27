#include <iostream>
#include <stdio.h>
using namespace std;
//使用函数指针，模板函数   定制删除器
template <class T>
void Delete(T*& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}
template <class T>
void Free(T*& p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
}
void FClose(FILE*& p)
{
	if (p)
	{
		fclose(p);
		p = NULL;
	}
}

template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = NULL, void (*pFun)(T*&) = Delete)
		: _ptr(ptr)
		, _pCount(new int(0))
		, _Dptr(pFun)
	{
		if (_ptr)
			*_pCount = 1;
	}
	SharedPtr(const SharedPtr& sp)
		: _ptr(sp._ptr)
		, _pCount(sp._pCount)
	{
		if(_ptr)
			(*_pCount)++;
	}
	SharedPtr& operator=(const SharedPtr& sp)
	{
		if (this != &sp)
		{
			_Realse();
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (*_pCount)
				(*_pCount)++;
		}
		return *this;
	}
	~SharedPtr()
	{
		_Realse();
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
	void _Realse()
	{
		if (_pCount && --(*_pCount) == 0)
		{
			_Dptr(_ptr);
			_ptr = NULL;
			delete _pCount;
			_pCount = NULL;
		}
	}
private:
	T* _ptr;
	int* _pCount;
	void (*_Dptr)(T*&);
};
int main()
{
	SharedPtr<int> sp1(new int(5));
	SharedPtr<double> sp3((double*)malloc(10), Free);
	SharedPtr<FILE> sp2(fopen("1.txt", "r"), FClose);
	return 0;
}


//使用仿函数，类模板  定制删除器
template <class T>
class Delete
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = NULL;
		}
	}
};
template <class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = NULL;
		}
	}
};
class Fclose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = NULL;
		}
	}
};

template<class T, class Dx = Delete<T>>
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
		if (_ptr)
			(*_pCount)++;
	}
	SharedPtr& operator=(const SharedPtr& sp)
	{
		if (this != &sp)
		{
			_Realse();
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (*_pCount)
				(*_pCount)++;
		}
		return *this;
	}
	~SharedPtr()
	{
		_Realse();
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
	void _Realse()
	{
		if (_pCount && --(*_pCount) == 0)
		{
			Dx()(_ptr);
			//delete _ptr;
			_ptr = NULL;
			delete _pCount;
			_pCount = NULL;
		}
	}
private:
	T* _ptr;
	int* _pCount;
};
int main()
{
	SharedPtr<int> sp1(new int(5));
	SharedPtr<double, Free<double>> sp3((double*)malloc(10));
	SharedPtr<FILE, Fclose> sp2(fopen("1.txt", "r"));
	return 0;
}#include <stdio.h>
//使用函数指针，模板函数   定制删除器
template <class T>
void Delete(T*& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}
template <class T>
void Free(T*& p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
}
void FClose(FILE*& p)
{
	if (p)
	{
		fclose(p);
		p = NULL;
	}
}

template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = NULL, void (*pFun)(T*&) = Delete)
		: _ptr(ptr)
		, _pCount(new int(0))
		, _Dptr(pFun)
	{
		if (_ptr)
			*_pCount = 1;
	}
	SharedPtr(const SharedPtr& sp)
		: _ptr(sp._ptr)
		, _pCount(sp._pCount)
	{
		if(_ptr)
			(*_pCount)++;
	}
	SharedPtr& operator=(const SharedPtr& sp)
	{
		if (this != &sp)
		{
			_Realse();
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (*_pCount)
				(*_pCount)++;
		}
		return *this;
	}
	~SharedPtr()
	{
		_Realse();
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
	void _Realse()
	{
		if (_pCount && --(*_pCount) == 0)
		{
			_Dptr(_ptr);
			_ptr = NULL;
			delete _pCount;
			_pCount = NULL;
		}
	}
private:
	T* _ptr;
	int* _pCount;
	void (*_Dptr)(T*&);
};
int main()
{
	SharedPtr<int> sp1(new int(5));
	SharedPtr<double> sp3((double*)malloc(10), Free);
	SharedPtr<FILE> sp2(fopen("1.txt", "r"), FClose);
	return 0;
}
#endif


#if 0
//使用仿函数，类模板  定制删除器
template <class T>
class Delete
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = NULL;
		}
	}
};
template <class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = NULL;
		}
	}
};
class Fclose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = NULL;
		}
	}
};

template<class T, class Dx = Delete<T>>
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
		if (_ptr)
			(*_pCount)++;
	}
	SharedPtr& operator=(const SharedPtr& sp)
	{
		if (this != &sp)
		{
			_Realse();
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (*_pCount)
				(*_pCount)++;
		}
		return *this;
	}
	~SharedPtr()
	{
		_Realse();
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
	void _Realse()
	{
		if (_pCount && --(*_pCount) == 0)
		{
			Dx()(_ptr);
			//delete _ptr;
			_ptr = NULL;
			delete _pCount;
			_pCount = NULL;
		}
	}
private:
	T* _ptr;
	int* _pCount;
};
int main()
{
	SharedPtr<int> sp1(new int(5));
	SharedPtr<double, Free<double>> sp3((double*)malloc(10));
	SharedPtr<FILE, Fclose> sp2(fopen("1.txt", "r"));
	return 0;
}