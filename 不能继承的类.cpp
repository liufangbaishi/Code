#include <iostream>
using namespace std;

// ��������1�ĸ���
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
// ���ܼ̳е��࣬�����ù��캯������������˽�У�����һ�����಻��ʵ������
// д������̬������һ���������ʵ����һ���ͷŸ���Ķ���
// ����ֻ���ڶ��ϴ������󣬲�����ջ��
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
// ��final�ؼ������ε��麯�����ܱ���д����final���ε��಻�ܱ��̳�
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
	//virtual void foo()//�޷���дfinal����
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
// ��Ԫ��ģ��
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

// ���û������Ϊ��Ԫ�࣬��ֻ������̳�
// virtual��̳� C�������B��ֱ�ӵ���A��Ĺ��캯����A��public�������C����B�Ĺ��캯��Ҳ�������
// û��virtual C���ȵ���B�๹�캯����B���ȵ���A�๹�캯����A��Ĺ��캯����B����˽�еģ���B�п��Է��ʵ�
// ���ԸĽ���������A��public��Ϊprivate��B���м̳�B����ΪA����Ԫ������B���Ե���A�Ĺ��캯�����������죬��C��̳�B�࣬������������̳У���ֱ�ӵ���A��Ĺ��캯������Ԫ���ܴ��ݣ����Բ��ܹ���
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
