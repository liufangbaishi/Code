#include <iostream>
using namespace std;
#if 1
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	void Destroy()
	{
		delete this;
	}
private:
	~A()
	{
		cout << "~A()" << endl;
	}
};
int main()
{
	A* a = new A();
	(*a).Destroy();
}
#else
class A
{
protected:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
public:
	static A* Construct()
	{
		return new A();
	}
	static void Destroy(A *p)
	{
		delete p;
		p = NULL;
	}
};
int main()
{
	A* p = A::Construct();
	A::Destroy(p);
}

#endif
#if 0
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	void* operator new(size_t size){};
	void operator delete(void *ptr) {};
};

int main()
{
	A a;
	//A *pa = new A();
	return 0;
}

#endif