//#include<iostream>
//using namespace std;
//class singleton
//{
//private:
//	singleton()
//	{
//		cout << "singleton()" << endl;
//	}
//	singleton(const singleton &s);
//	singleton& operator=(const singleton& s);
//public:
//	static singleton* getInstance()
//	{
//		if (_instance == NULL)
//			_instance = new singleton();
//		return _instance;
//	}
//
//	static void Release()
//	{
//		if (NULL != _instance)
//		{
//			delete _instance;
//			_instance = NULL;
//		}
//	}
//private:
//	static singleton* _instance;
//};
//singleton* singleton::_instance = NULL;
//
//int main()
//{
//	singleton* p = singleton::getInstance();
//	return 0;
//}

#include<iostream>
using namespace std;
class singleton
{
private:
	singleton()
	{
		cout << "singleton()" << endl;
	}
public:
	static singleton* getInstance()
	{
		return _instance;
	}

private:
	static singleton* _instance;
};
singleton* singleton::_instance = new singleton();

int main()
{
	singleton* p = singleton::getInstance();
	return 0;
}