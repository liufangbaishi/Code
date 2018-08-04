#include <iostream>
using namespace std;
////////////////////////////////////////写时拷贝/////////////////////////////
class String
{
public:
	String(const char* pStr = "")
	{
		if (NULL == pStr)
			pStr = "";
		_pStr = new char[strlen(pStr) + 1 + 4];
		_pStr = _pStr + 4;
		strcpy(_pStr, pStr);
		GetReference() = 1;
	}
	String(const String& s)
		: _pStr(s._pStr)
	{
		GetReference()++;
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			Release();
		    _pStr = s._pStr;
			GetReference()++;
		}
		return *this;
	}
	~String()
	{
		Release();
	}
	char& operator[](size_t index)
	{
		if (GetReference() > 1)
		{
			String str(_pStr);
			swap(_pStr, str._pStr);
		}
		return _pStr[index];
	}
private:
	int& GetReference()
	{
		return *(int*)(_pStr - 4);
	}
	void Release()
	{
		if (0 == --GetReference() && _pStr)
		{
			_pStr = _pStr - 4;
			delete[] _pStr;
			_pStr = NULL;
		}
	}
private:
	char* _pStr;
};
int main()
{
	String s1("Hello");
	//String s2(s1);
	String s3;
	s3 = s1;
	s3[1] = 'w';
	return 0;
}
