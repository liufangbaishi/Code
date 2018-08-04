#include <iostream>
using namespace std;
class String
{
public:
	friend ostream& operator<<(ostream& _cout, const String& s)
	{
		_cout << s._pStr;
		return _cout;
	}
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
	//String(const String& s)//浅拷贝 有错
	//{
	//	_pStr = s._pStr;
	//}
	String(const String& s)//拷贝构造 深拷贝 第一种常见写法
	{
		_pStr = new char[strlen(s._pStr) + 1];
		strcpy(_pStr, s._pStr);
	}
	//拷贝构造 第二种写法  野指针？vs2013的编译器this->_pStr为0x0，所以不会出错，vs2008的编译器this->_pStr为0xcccccccc，会出错
	String(const String& s)//this指针不为0，交换后，tmp变为野指针，析构时进入if语句内，程序会挂掉
		: _pStr(NULL)      //_pStr初值为0，交换后tmp._pStr也为0，析构时不会进if，不会出现问题
	{
		String tmp(s._pStr);
		swap(_pStr, tmp._pStr);
	}
	~String()
	{
		if (_pStr)
		{
			delete[] _pStr;
			_pStr = NULL;
		}
	}
	String& operator=(const String& s) // 赋值运算符重载  第一种写法，常见写法
	{
		if (this != &s)
		{
			char* Temp = new char[strlen(s._pStr) + 1];
			strcpy(Temp, s._pStr);
			delete[] _pStr;
			_pStr = Temp;
		}
		return *this;
	}
	// 赋值运算符重载  第二种写法
	String& operator=(const String& s)//用s构造tmp对象，交换当前指针和tmp，返回*this
	{
		if (this != &s)
		{
			String tmp(s);//拷贝构造
			swap(_pStr, tmp._pStr);
		}
		return *this;
	}
	// 赋值运算符重载  第三种写法
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s._pStr);//构造函数
			swap(_pStr, tmp._pStr);
		}
		return *this;
	}
	// 赋值运算符重载  第四种写法
	String& operator=(String s)//值传递，拷贝构造构建临时变量
	{
		swap(_pStr, s._pStr);
		return *this;
	}
	
	///////////////////////////////////////////////其他函数/////////////////////////////////////
	size_t Size()const
	{
		char* begin = _pStr;
		char* end = _pStr;
		while (*end++)
			;
		return end - begin - 1;
	}
	size_t Lengh()const
	{
		char* begin = _pStr;
		char* end = _pStr;
		while (*end++)
			;
		return end - begin - 1;
	}
	char& operator[](size_t index)
	{
		return _pStr[index];
	}
	const char& operator[](size_t index)const
	{
		return _pStr[index];
	}
	bool operator>(const String& s)
	{
		char* s1 = _pStr;
		char* s2 = s._pStr;
		while (*s1 == *s2)
		{
			if (*s1 == '\0')
				return false;
			s1++;
			s2++;
		}
		if (*s1 > *s2)
			return true;
		return false;
	}
	bool operator<(const String& s)
	{
		char* s1 = _pStr;
		char* s2 = s._pStr;
		while (*s1 == *s2)
		{
			if (*s1 == '\0')
				return false;
			s1++;
			s2++;
		}
		if (*s1 < *s2)
			return true;
		return false;
	}
	bool operator==(const String& s)
	{
		char* s1 = _pStr;
		char* s2 = s._pStr;
		while (*s1 == *s2)
		{
			if (*s1 == '\0')
				return true;
			s1++;
			s2++;
		}
		return false;
	}
	bool operator!=(const String& s)
	{
		char* s1 = _pStr;
		char* s2 = s._pStr;
		if (s1 == s2)
			return false;
		return true;
	}
	void Copy(const String& s)
	{
		delete _pStr;
		_pStr = new char[strlen(s._pStr) + 1];
		char* s1 = _pStr;
		char* s2 = s._pStr;
		while (*s1++ = *s2++)
			;
	}
	bool strstr(const String& s)
	{
		char* s1 = _pStr;
		char* s2 = s._pStr;
		char* cur = _pStr;
		if (s._pStr == '\0')
			return true;
		while (*cur)
		{
			s1 = cur;
			s2 = s._pStr;
			while (*s1 && *s2 && (*s1 == *s2))
			{
				s1++;
				s2++;
			}
			if (*s2 == '\0')
				return true;
			cur++;
		}
		return false;
	}
	String& operator+=(const String& s)
	{
		char* tmp = new char[strlen(_pStr) + strlen(s._pStr) + 1];		
		char* s2 = s._pStr;
		strcpy(tmp, _pStr);
		delete _pStr;
		_pStr = tmp;
		char* s1 = _pStr;
		strcpy(s1, tmp);
		//strcat
		while (*s1 != '\0')
			s1++;
		while (*s1++ = *s2++)
			;
		return *this;
	}
private:
	char *_pStr;
};
int main()
{
	String s1("Hello");
	String s3("H");
	String s4;
	s3 += s1;
	//cout<<s1.strstr(s3)<<endl;
	//cout<<s1.strstr(s4)<<endl;
	cout << s3 << endl;

	//String s4;
	//s4 += s1;
	//cout << s4 << endl;
	/*s3.Copy(s1);
	cout << s3 << endl;*/
	//cout << s1.Size() << endl;
	//cout << s1.Lengh() << endl;
	//s1[2] = 'w';
	//cout << s1 << endl;
	//if (s1 != s2)
	//	cout << "!=" << endl;


	//String s1;
	//String s2("abc");
	//String s3(s2);
	//cout << s2 << endl;
	//cout << s3 << endl;
	//String s4;
	//s4 = s2;
	//cout << s4 << endl;
	return 0;
}