#define _CRT_SECURE_NO_WARNINGS 1
#if 1
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
			for (size_t i = oldsize; i < newSize;i++)
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
		return *_start;
	}
	const T& Front()const
	{
		return *_start;
	}
	T& Back()
	{
		return *(_finish-1);
	}
	const T& Back()const
	{
		return *(_finish-1);
	}
	void Clear()
	{
		_finish = _start;
	}
	template<class T>
	friend ostream& operator<<(ostream& _cout, const Vector<T>& v)
	{
		for (size_t i = 0; i < v.Size(); i++)
			_cout << v._start[i] <<" ";
		return _cout;
	}
private:
	void _CheckCapacity()
	{
		size_t size = Size();
		size_t capacity = Capacity();
		size_t newCapacity = 2 * capacity + 3;
		if (_finish==_endofstorage)
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
class String
{
public:
	String(const char* pStr = "")
	{
		if (pStr == NULL)
		{
			_pStr = new char[1];
			*_pStr = '\0';
		}
		else
		{
			_pStr = new char[strlen(pStr) + 1];
			strcpy(_pStr, pStr);
		}
	}
	String(const String& s)
		: _pStr(new char[strlen(s._pStr)+1])
	{
		strcpy(_pStr, s._pStr);
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* tmp = new char[strlen(s._pStr) + 1];
			strcpy(tmp, s._pStr);
			delete[] _pStr;
			_pStr = tmp;
		}
		return *this;
	}
	~String()
	{
		if (_pStr)
		{
			delete[] _pStr;
			_pStr = NULL;
		}
	}
	friend ostream& operator<<(ostream& _cout, const String s)
	{
		_cout << s._pStr;
		return _cout;
	}
private:
	char* _pStr;
};
//void StringTest()
//{
//	String s[] = { "123","456" };
//	Vector<String> v1;
//	Vector<String> v2(s, sizeof(s)/sizeof(s[0]));
//	/*cout << v2 << endl;
//	v1.PushBack("abc");
//	v1.PushBack("def");
//	v1.PushBack("123");
//	cout << v1 << endl;*/
//	cout << v2.Size() << endl;
//	cout << v2.Capacity() << endl;
//	//cout << v1.Back() << endl;
//	//cout << v1.Empty() << endl;
//	//v1.Erase(2);
//	//cout << v1 << endl;
//	//cout << v1.Front() << endl;
//	//v1.Insert(0, "852");
//	//cout << v1 << endl;
//	//v1.PopBack();
//	//cout << v1 << endl;
//	//v1.Clear();
//	//cout << v1 << endl;
//	cout << v2 << endl;
//	v2.Resize(8,"123");
//	cout << v2.Size() << endl;
//	cout << v2.Capacity() << endl;
//	cout << v2 << endl;
//	//cout << v1[2] << endl;
//	//Vector<String> v2;
//	//v2 = v1;
//	//cout << v2 << endl;
//	//Vector<String> v3(v1);
//	//cout << v3 << endl;
//	//String s1("abc");
//	//String s2(s1);
//	//String s3 = s1;
//	//cout << s1 << endl;
//	//cout << s2 << endl;
//	//cout << s3 << endl;
//}
int main()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(1);
	v.PushBack(1);

	Vector<int>::Iterator it = v.Begin();
	Vector<int>::Iterator begin = v.Begin();
	v.Insert(0, 20);
	for (it = v.Begin(); it < v.End(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}

//
//void IntTest()
//{
//	Vector<int> v1;
//	int arr[5] = { 1, 2, 3, 4, 5 };
//	Vector<int> v2(arr, sizeof(arr) / sizeof(arr[0]));
//	cout << v2 << endl;
//	cout << v2.Size() << endl;
//	cout << v2.Capacity() << endl;
//	v2.Resize(2);
//	cout << v2 << endl;
//	cout << v2.Size() << endl;
//	cout << v2.Capacity() << endl;
//	v2.Resize(4,520);
//	cout << v2 << endl;
//	cout << v2.Size() << endl;
//	cout << v2.Capacity() << endl;
//
//
//	cout << v2[2] << endl;
//	//cout << v2 << endl;
//	//Vector<int> v3;
//	//v3 = v2;
//	//cout << v3 << endl;
//	//v1.PopBack();
//
//	//v2.Insert(0, 10);
//	//cout << v2 << endl;
//	//v2.Erase(5);
//	//cout << v2 << endl;
//
//	//v2.PushBack(6);
//	//v2.PushBack(7);
//	//cout << v2 << endl;
//	//v2.PopBack();
//	//cout << v2 << endl;
//	////cout << v2[2] << endl;
//
//	//cout<<v2.Front()<<endl;
//	//cout << v2.Back() << endl;
//	//v2.Clear();
//	//cout << v2 << endl;
//}
#endif


