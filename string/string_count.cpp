#include <iostream>
using namespace std;
/////////////////////////////////////引用计数////////////////////////////////////////
class String
{
public:
	String(const char* pStr = "")
		:_count(new int(1))
	{
		if (NULL == pStr)
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
		: _count(s._count)
		, _pStr(s._pStr)
	{
		(*_count)++;
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			if (0 == --(*_count))//s3=s2
			{
				delete[] _pStr;
				delete _count;
			}
			_pStr = s._pStr;//s2=s3
			_count = s._count;
			(*_count)++;
		}
		return *this;
	}
	~String()
	{
		if (0 == --(*_count) && _pStr)
		{
			delete[] _pStr;
			_pStr = NULL;
			delete _count;
			_count = NULL;
		}
	}
private:
	char* _pStr;
	int * _count;
};
int main()
{
	String s1("hello");
	String s2(s1);
	String s3;
	s3 = s2;
	s2 = s3;
	s3 = s1;
	s1 = s3;
	return 0;
}