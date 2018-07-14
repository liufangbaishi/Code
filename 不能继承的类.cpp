#include <iostream>
using namespace std;

// 二进制中1的个数
//int Number(int n)
//{
//	unsigned int flag = 1;
//	int count = 0;
//	while (flag)
//	{
//		if (n & flag)
//			count++;
//		flag = flag << 1;
//	}
//	return count;
//}
//int main()
//{
//	int ret = Number(-1);
//	return 0;
//}

#if 0
// 不能继承的类，即：让构造函数和析构函数私有，这样一来，类不能实例化，
// 写两个静态方法，一个返回类的实例，一个释放该类的对象
// 这样只能在堆上创建对象，不能在栈上
class AA
{
private:
	AA(){ cout << "AA()" << endl; }
	~AA(){ cout << "~A()" << endl; }
public:
	static void test(AA* a)
	{
		cout << "AA::test()" << endl;
	}
	static AA* construct(int n)
	{
		AA *a = new AA();
		a->_a = n;
		return a;
	}
	static void destroy(AA* aa)
	{
		delete aa;
	}
private:
	int _a;
};
class BB : public AA
{
};
void test()
{
	//BB b;
	AA* a = AA::construct(3);
	AA::test(a);
	AA::destroy(a);
}
int main()
{
	test();
	return 0;
}
//#else
// 被final关键字修饰的虚函数不能被重写，被final修饰的类不能被继承
class A
{
public:
	virtual void foo() final
	{
		cout << "A" << endl;
	}
};

class B final : public A
{
public:
	//virtual void foo()//无法重写final函数
	//{
	//	cout << "B" << endl;
	//}
};

class C : public B
{
};
int main()
{
	B b;
	A &a = b;
	a.foo();
	return 0;
}
#endif

#if 0
// 友元和模板
template <class T>
class A
{
	friend T;
private:
	int a;
	A()
	{
		cout << "A()" << endl;
	}
};

// 如果没有声明为友元类，而只是虚拟继承
// virtual虚继承 C类会跳过B，直接调用A类的构造函数，A是public不会出错，C调用B的构造函数也不会出错
// 没有virtual C类先调用B类构造函数，B类先调用A类构造函数，A类的构造函数在B类是私有的，在B中可以访问到
// 所以改进方法：将A的public改为private，B公有继承B声明为A的友元，这样B可以调用A的构造函数，正常构造，而C类继承B类，但是由于是虚继承，将直接调用A类的构造函数，友元不能传递，所以不能构造
class B :public virtual A<B>
{
public:
	B()
	{
		cout << "B()" << endl;
	}
};

class C :public B
{
public:
	C()
	{
		cout << "C()" << endl;
	}
};

int main()
{
	B b;
	//C c;
	return 0;
}
#endif


//class AA
//{
//public:
//	AA(int n = 3)
//	{ 
//		cout << "AA()" << endl; 
//	}
//	~AA(){ cout << "~A()" << endl; }
//	void test1()
//	{
//		cout << "AA::test1()" << endl;
//	}
//private:
//	int _a;
//};
//class BB : private AA
//{
//public:
//	BB(int b)
//	{
//		cout << "B()" << endl;
//	}
//	void test2()
//	{
//		cout << "BB::test2()" << endl;
//	}
//	~BB(){ cout << "~B()" << endl; }
//private:
//	int _b;
//};
//void test()
//{
//	AA a(3);
//	BB b(4);
//	b.test2();
//	b.~BB();
//}
//int main()
//{
//	test();
//	return 0;
//}


class B
{
public:
	B()
	{

	}
	int b1;
};
class D :virtual public B
{
public:
	D()
	{

	}
	int d1;
};
class A : public D
{
public:
	A()
	{

	}
	int _a;
};
int main()
{
	A a;
	a._a = 1;
	a.b1 = 2;
	a.d1 = 3;
	return 0;
}
